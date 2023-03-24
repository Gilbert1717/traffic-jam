#include "player.h"

Position::Position()
{
    
}


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Player::Player()
{
    
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    this->position = *(position);
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    if (turnDirection == TurnDirection::TURN_LEFT){
        if (this->direction == Direction::NORTH) {
            this->direction = Direction::WEST;
        }
        else if (this->direction == Direction::WEST) {
            this->direction = Direction::SOUTH;
        }
        else if (this->direction == Direction::SOUTH) {
            this->direction = Direction::EAST;
        }
        else if (this->direction == Direction::EAST) {
            this->direction = Direction::NORTH;
        }
    }

    else if (turnDirection == TurnDirection::TURN_RIGHT){
        if (this->direction == Direction::NORTH) {
            this->direction = Direction::EAST;
        }
        else if (this->direction == Direction::EAST) {
            this->direction = Direction::SOUTH;
        }
        else if (this->direction == Direction::SOUTH) {
            this->direction = Direction::WEST;
        }
        else if (this->direction == Direction::WEST) {
            this->direction = Direction::NORTH;
        }
    }

}

Position Player::getNextForwardPosition()
{
    int x = this->position.x;
    int y = this->position.y;
    if(this->direction == Direction::EAST){
        y = this->position.y + 1;
    }
    else if(this->direction == Direction::NORTH){
        x = this->position.x - 1;
    }
    else if(this->direction == Direction::WEST){
        y = this->position.y - 1;
    }
    else{
        x = this->position.x + 1;
    }
    
    return Position(x,y);
}

void Player::updatePosition(Position position)
{
    this->moves += 1;
    this->position = position;
}

void Player::displayDirection()
{
    if (this->direction == Direction::EAST){
        printf(DIRECTION_ARROW_OUTPUT_EAST);
    }
    else if (this->direction == Direction::NORTH){
        printf(DIRECTION_ARROW_OUTPUT_NORTH);
    }
    else if (this->direction == Direction::WEST){
        printf(DIRECTION_ARROW_OUTPUT_WEST);
    }
    else{
        printf(DIRECTION_ARROW_OUTPUT_SOUTH);
    }
}
