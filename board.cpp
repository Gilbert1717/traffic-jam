#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{
    this->board =  new std::vector<std::vector<Cell> > (10 , vector<Cell> (10, Cell::EMPTY));
}

Board::~Board()
{
    delete this->board;
    this->board = nullptr;
}

void Board::load(int boardId)
{
    if (boardId == 1) {
        this->board = new std::vector<std::vector<Cell> > (BOARD_1);
    }

    else if (boardId == 2) {
        this->board = new std::vector<std::vector<Cell> > (BOARD_2);
    }   
    else {
        std::cout << "Board ID does not exist\n";
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
    std::cout << std::endl;
    std::cout << "| ";
    for (int i=0; i < (this->board) -> size(); ++i){
        std::cout << "|" << i;
    }
    std::cout << "|" << std::endl;
    for (int i=0; i < (this->board) -> size(); ++i){
        std::cout << "|" << i;
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



