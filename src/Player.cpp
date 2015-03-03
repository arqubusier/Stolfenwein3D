#include "Player.h"


Player::Player()
{

}

Player::Player(float x, float y, float heading = 0)
{
	position.x = x;
	position.y = y;
	this->heading = heading;
}

Player::~Player()
{
}
 