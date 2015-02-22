#pragma once
#include "vector2d.h"
class player
{
public:
	player(float x, float y, float heading);
	~player();
	vector2d position;
	float heading;
private:
	player();

};
