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

void Player::draw(SDL_Renderer *ren, SDL_Window *win){
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
    SDL_RenderDrawPoint(ren, (int) position.x, (int) position.y);
}
