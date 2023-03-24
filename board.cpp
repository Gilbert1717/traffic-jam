#include "board.h"
// #include <iostream>

using std::vector;


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
    int numberOfBlocks = int(floor(size*size*percent));
    placeBlocker(numberOfBlocks);
}

void Board::placeBlocker(int numberOfBlocks){
    int randX;
    int randY;
    for (int i = 0; i < numberOfBlocks; i++){
        do {randX = rand() % this->size;
        randY = rand() % this->size;}
        while((*(this->board))[randX][randY] == Cell::BLOCKED);
        (*(this->board))[randX][randY] = Cell::BLOCKED;
    }
}

bool Board::placePlayer(Position position)
{
    if ((*(this->board))[position.x][position.y] != Cell::BLOCKED) {
        (*(this->board))[position.x][position.y] = Cell::PLAYER;
        return true;
    }
    std::cout << "This init position is blocked! Please re-init\n";
    return false; 
}

PlayerMove Board::movePlayerForward(Player* player)
{
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
}



