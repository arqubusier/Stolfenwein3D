#include "vector2d.h"


vector2d::vector2d()
: x(component[0]), y(component[1])
{
	component[0] = 0;
	component[1] = 0;
}
vector2d::vector2d(float x, float y)
: x(component[0]), y(component[1])
{
	component[0] = x;
	component[1] = y;
}


vector2d::~vector2d()
{
}
