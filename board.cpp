#include "board.h"
// #include <iostream>

using std::vector;

// const vector<vector<Cell>> Board::BOARD_1 =
// {
//     { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
//     { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
// };

// const vector<vector<Cell>> Board::BOARD_2 =
// {
//     { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
//     { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
// };
// new std::vector<std::vector<Cell> > (size , vector<Cell> (size, Cell::EMPTY))
Board::Board()
{
    this->board =  nullptr;
    this->size = 0;
}

Board::~Board()
{
    delete this->board;
    this->board = nullptr;
}

int Board::getSize(){
    return this->size;
}

void Board::load(int size, double percent){
    this->board = new std::vector<std::vector<Cell> > (size , vector<Cell> (size, Cell::EMPTY));
    this->size = size;
    int totalPlot = size*size;
    int blockAmount = int(floor(totalPlot*percent));
    std::cout << int(totalPlot*percent) << "floor\n";
    int blockPosition[blockAmount];
    for (int i = 0; i < blockAmount; i++){
        int randPosition = rand() % totalPlot;
        while (in_array(blockPosition, blockAmount, randPosition)) {
            randPosition = rand() % totalPlot;
        }
        blockPosition[i] = randPosition;
    }
    std::cout << std::endl;
    placeBlocker(blockPosition, blockAmount, size);
}

void Board::placeBlocker(int arr[], int arrSize, int size){
    for (int i = 0; i < arrSize; i++){
        int row = arr[i]/size;
        int col = arr[i]%size;
        (*(this->board))[row][col] = Cell::BLOCKED;
    }
    std::cout << std::endl;
}

bool Board::in_array(int arr[], int arrSize, int needle){
    bool result = false;
    for(int i=0; i<arrSize; i++)
        if (arr[i] == needle)
            result = true;
    return result;
}
// void Board::load(int boardId)
// {
//     std::cout << boardId << std::endl;
//     if (boardId == 1) {
//         this->board = new std::vector<std::vector<Cell> > (BOARD_1);
//     }

//     else if (boardId == 2) {
//         this->board = new std::vector<std::vector<Cell> > (BOARD_2);
//     }   
//     else {
//         std::cout << "Board ID does not exist\n";
//     } 
// }

bool Board::placePlayer(Position position)
{
    // TODO
    if ((*(this->board))[position.x][position.y] != Cell::BLOCKED) {
        (*(this->board))[position.x][position.y] = Cell::PLAYER;
        return true;
    }
    std::cout << "This init position is blocked! Please re-init\n";
    return false; // feel free to revise this line, depending on your implementation.
}

PlayerMove Board::movePlayerForward(Player* player)
{
    // TODO
    Position position = player->getNextForwardPosition();
    if (position.x < 0 || position.x >= (this->board) -> size() ||
        position.y < 0 || position.y >= (this->board) -> at(0).size()){
            return OUTSIDE_BOUNDS;
    }
    else if ((*(this->board))[position.x][position.y] == Cell::BLOCKED){
        return CELL_BLOCKED;
    }
    
    (*(this->board))[position.x][position.y] = Cell::PLAYER;
    (*(this->board))[player->position.x][player->position.y] = Cell::EMPTY;
    player->updatePosition(position);
    return PLAYER_MOVED; 
}

void Board::display(Player* player)
{
    int block = 0;
    std::cout << "| ";
    for (int i=0; i < (this->board) -> size(); ++i){
        std::cout << "|" << i%10;
    }
    std::cout << "|" << std::endl;
    for (int i=0; i < (this->board) -> size(); ++i){
        std::cout << "|" << i%10;
        for (int j=0; j < (this->board) -> at(i).size(); ++j) {
            std::cout << "|";
            if((*(this->board))[i][j] == Cell::BLOCKED) {
                block ++;
                std::cout << "*";
            } 
            else if((*(this->board))[i][j] == Cell::EMPTY) {
                std::cout << " ";
            } 
            else{
                player->displayDirection();
            };
        }
        std::cout << "|" << std::endl;
    };
    std::cout << block << std::endl;
    
}



