#include "game.h"
#include "helper.h"
#include "player.h"
#include <regex>


const std::regex loadBoardRegex ("(1[0-9]|20)(,0.)[1-9]");
const std::regex initPlayerRegex ("(north|east|south|west)");
const std::string error1 = "Invalid input";
const std::string error2 = "Invalid position";

Game::Game()
{
    this->board = new Board();
    this->player = new Player();
}

Game::~Game()
{
    delete this->board;
    this->board = nullptr;

    delete this->player;
    this->player = nullptr;
}


void Game::start()
{
    displayGameInstruction();
    if (loadBoard()) {
        this->board -> display(this->player);
        if(initializePlayer()){
            play();
        }
    };
}

bool Game::loadBoard()
{
    std::string input;
    do {
        input = handleLoadInput();
        if (input == error1){
            displayGameInstruction();
        }
    }while(input == error1);

    if (input == COMMAND_QUIT){
        return false;
    }

    else {
        generateBoard(input);
        return true; 
    }
}

void Game::generateBoard(std::string input){
    std::vector<std::string> inputData;
    Helper::splitString(input,inputData,",");

    int size = std::stoi(inputData[0]);
    double percentage = std::stod(inputData[1]);  

    (this->board) -> load(size,percentage);  

}

std::string Game::handleLoadInput(){
    std::string input; 
    std::vector<std::string> inputTokens;
    
    std::getline(std::cin >> std::ws, input);;
    Helper::splitString(input,inputTokens," ");

    if(inputTokens[0] == COMMAND_QUIT){
        if(input.size() == 4)
            return COMMAND_QUIT;
    }

    else if(inputTokens[0] == COMMAND_GENERATE_RANDOM){
        if (std::regex_match (inputTokens[1], loadBoardRegex)){
            return inputTokens[1];
        }  
    }

    Helper::printInvalidInput();
    return error1;
}

bool Game::initializePlayer()
{
    std::string input;
    std::vector<std::string> inputData;
    do {
        input = handleInitInput();
        if (input == error1){
            displayGameInstruction();
        }
        else if (std::regex_match (input, loadBoardRegex)){
            generateBoard(input);
            this->board->display(this->player);
        }
    }while(input == error1 || std::regex_match (input, loadBoardRegex));

    if (input == COMMAND_QUIT){
        return false;
    } 

    else {
        Helper::splitString(input,inputData,",");
        int x = std::stoi(inputData[0]);
        int y = std::stoi(inputData[1]);
        Position* initPositionPtr = new Position(x,y);
        this->player->initialisePlayer(initPositionPtr, directionConverter(inputData[2]));
        this->board->display(this->player);
        return true;
    }
        
    
}

void Game::play()
{
    std::cout << "start game\n";
    std::string input;
    do {
        input = handlePlayInput();
        if (input == error1){
            displayGameInstruction();
        }
    }while(input != COMMAND_QUIT);
}



std::string Game::handleInitInput(){
    std::string input; 
    std::getline(std::cin >> std::ws, input);

    std::vector<std::string> inputTokens;
    Helper::splitString(input,inputTokens," ");

    std::vector<std::string> inputData;
    Helper::splitString(inputTokens[1],inputData,",");
    if(inputTokens[0] == COMMAND_QUIT && input.size() == 4){
        return COMMAND_QUIT;
    }

    else if(inputTokens[0] == COMMAND_INIT && initCommandCheck(inputData)){ 
        int x = std::stoi(inputData[0]);
        int y = std::stoi(inputData[1]);
        if (!this->board->placePlayer(Position(x,y))){
            this->board->display(this->player);
            return error2;
        }
        return inputTokens[1];
    }

    else if(inputTokens[0] == COMMAND_GENERATE_RANDOM 
            && std::regex_match (inputTokens[1], loadBoardRegex)){
        return inputTokens[1];   
    }
    
    Helper::printInvalidInput();
    return error1;
}

bool Game::initCommandCheck(std::vector<std::string> inputData) {
    
    if (Helper::isNumber(inputData[0]) && Helper::isNumber(inputData[1])){
        int x = std::stoi(inputData[0]);
        int y = std::stoi(inputData[1]);

        if (x >= 0 && x < this->board->getSize() &&
            y >= 0 && y < this->board->getSize() &&
            std::regex_match(inputData[2],initPlayerRegex)){
                return true;
            }
    }
    return false;
}

bool Game::validatePosition(){
    PlayerMove moveResult = this->board->movePlayerForward(this->player);
    if (moveResult == PlayerMove::OUTSIDE_BOUNDS){
        std::cout << "Error: cannot move forward because the road is ended\n";
        return false;
    }
    else if (moveResult == PlayerMove::CELL_BLOCKED){
        std::cout << "Error: cannot move forward because the road is blocked\n";
        return false;
    }
    return true;
}

std::string Game::handlePlayInput(){
    std::string input; 
    std::getline(std::cin >> std::ws, input);
    if(input == COMMAND_QUIT){
        std::cout << "Total player moves: " << this->player->moves << std::endl;
        return COMMAND_QUIT;
    }

    if(input == COMMAND_FORWARD || input == COMMAND_FORWARD_SHORTCUT){
        //Position validation
        if(validatePosition()){
            this->board->display(this->player);
            return COMMAND_FORWARD;
        }
        else{
            return error2;
        }
    }

    if(input == COMMAND_TURN_RIGHT || input == COMMAND_TURN_RIGHT_SHORTCUT){
        this->player->turnDirection(TurnDirection::TURN_RIGHT);
        this->board->display(this->player);
        return COMMAND_TURN_RIGHT_SHORTCUT;
    }

    if(input == COMMAND_TURN_LEFT || input == COMMAND_TURN_LEFT_SHORTCUT){
        this->player->turnDirection(TurnDirection::TURN_LEFT);
        this->board->display(this->player);
        return COMMAND_TURN_LEFT_SHORTCUT;
    }
    
    Helper::printInvalidInput();
    return error1;
}


void Game::displayGameInstruction() {
    std::cout << std::endl;
    std::cout << "You can use the following commands to play the game:\n\n";
    std::cout << "generate <d>,<p>\n";
    std::cout << "\td: the dimension of the game board to be generated\n";
    std::cout << "\tp: the probability of the blocks on board to be generated randomly\n";
    std::cout << "init <x>,<y>,<direction>\n";
    std::cout << "\tx: horizontal position of the car on the board (between 0 & 9)\n";
    std::cout << "\ty: vertical position of the car on the board (between 0 & 9)\n";
    std::cout << "\tdirection: direction of the car's movement (north, east, south, west)\n";
    std::cout << "forward (or f)\n";
    std::cout << "turn_left (or l)\n";
    std::cout << "turn_right (or r)\n";
    std::cout << "quit\n\n";
}

Direction Game::directionConverter(std::string s){
    if (s == DIRECTION_NORTH){
        return Direction::NORTH;
    }
    else if (s == DIRECTION_EAST){
        return Direction::EAST;
    }
    else if (s == DIRECTION_SOUTH){
        return Direction::SOUTH;
    }
    else{
        return Direction::WEST;
    }
}





