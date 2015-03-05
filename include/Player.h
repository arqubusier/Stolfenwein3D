#ifndef Player2D_H
#define Player2D_H

#include "Vector2d.h"
class Player
{
public:
	Player(float x, float y, float heading);
	~Player();
	Vector2d position;
	float heading;
private:
	Player();

};

#endif
