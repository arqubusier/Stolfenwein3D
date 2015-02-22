#include "Vector2d.h"


Vector2d::Vector2d()
: x(component[0]), y(component[1])
{
	component[0] = 0;
	component[1] = 0;
}
Vector2d::Vector2d(float x, float y)
: x(component[0]), y(component[1])
{
	component[0] = x;
	component[1] = y;
}


Vector2d::~Vector2d()
{
}
