#include "game.h"
#include "helper.h"
#include "player.h"
#include <regex>



using std::string;
const std::regex loadBoardRegex ("(load )[1-2]");
const std::regex initPlayerRegex ("[0-9](,)[0-9](,)(north|east|south|west)");

Game::Game()
{
    // TODO
    this->board = new Board();
    this->player = new Player();
}

Game::~Game()
{
    // TODO
    delete this->board;
    this->board = nullptr;

    delete this->player;
    this->player = nullptr;
}


void Game::start()
{
    displayGameInstruction();
    this->board -> display(this->player);
    if (loadBoard()) {
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
    }while(input == "0");

    if (input == COMMAND_QUIT){
        return false;
    }

    int boardId = std::stoi(input);
    (this->board) -> load(boardId);
    this->board->display(this->player);

    return true; 
}

bool Game::initializePlayer()
{
    std::string input;
    std::vector<std::string> inputData;
    do {
        input = handleInitInput();
        std::cout << input << std::endl;
        if (input == "1" || input == "2") {
            int boardId = std::stoi(input);
            (this->board) -> load(boardId);
            this->board->display(this->player);
        }
        if (input == "0"){
            displayGameInstruction();
        }
    }while(input != COMMAND_QUIT && input != "4" );

    if (input == COMMAND_QUIT){
        return false;
    } 

    else {
        std::cout << input << std::endl;
        this->board->display(this->player);
        return true;
    }
        
    
}

void Game::play()
{
    //TODO
    std::cout << "start game\n";
    std::string input;
    do {
        input = handlePlayInput();
        if (input == "0"){
            displayGameInstruction();
        }
    }while(input != COMMAND_QUIT);

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

    else if(inputTokens[0] == COMMAND_LOAD){
        if(inputTokens[1] == "1" || inputTokens[1] == "2"){
            return inputTokens[1];
        }      
    }

    Helper::printInvalidInput();
    displayGameInstruction();
    return "0";
}

std::string Game::handleInitInput(){
    std::string input; 
    std::vector<std::string> inputTokens;
    
    std::getline(std::cin >> std::ws, input);
    Helper::splitString(input,inputTokens," ");
    if(inputTokens[0] == COMMAND_QUIT){
        if(input.size() == 4)
            return COMMAND_QUIT;
    }

    else if(inputTokens[0] == COMMAND_INIT){
        if(std::regex_match (inputTokens[1], initPlayerRegex)){
            std::vector<std::string> inputData;
            Helper::splitString(inputTokens[1],inputData,",");
            int x = std::stoi(inputData[0]);
            int y = std::stoi(inputData[1]); 
            this->player->initialisePlayer(new Position(x,y),directionConverter(inputData[2]));
            if(this->board->placePlayer(this->player->position)){
                return "4";
            }
            else{
                return "3";
            }
        }
    }

    else if(inputTokens[0] == COMMAND_LOAD){
        if(inputTokens[1] == "1" || inputTokens[1] == "2"){
            return inputTokens[1];
        }      
    }
    
    Helper::printInvalidInput();
    return "0";
}

std::string Game::handlePlayInput(){
    std::string input; 
    std::getline(std::cin >> std::ws, input);
    if(input == COMMAND_QUIT){
        std::cout << "Total player moves: " << this->player->moves << std::endl;
        return COMMAND_QUIT;
    }

    if(input == COMMAND_FORWARD || input == COMMAND_FORWARD_SHORTCUT){
        //TODO: Position validation
        PlayerMove moveResult = this->board->movePlayerForward(this->player);
        if (moveResult == PlayerMove::OUTSIDE_BOUNDS){
            std::cout << "Error: cannot move forward because the road is ended\n";
        }
        else if (moveResult == PlayerMove::CELL_BLOCKED){
            std::cout << "Error: cannot move forward because the road is blocked\n";
        }
        
        this->board->display(this->player);
        return COMMAND_FORWARD;
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
    return "0";
}


void Game::displayGameInstruction() {
    std::cout << std::endl;
    std::cout << "You can use the following commands to play the game:\n";
    std::cout << "load <g>\n";
    std::cout << "\tg: number of the game board to load\n";
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





