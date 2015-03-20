#ifndef Player2D_H
#define Player2D_H
#include <SDL.h>

#include "Vector2d.h"
class Player
{
public:
	Player(float x, float y, float heading);
	~Player();
	Vector2d position;
	float heading;

    //Consider finding better name
    void draw(SDL_Renderer *ren, SDL_Window *win);
private:
	Player();

};

#endif
