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
	this->x = x;
	this->y = y;
}


Vector2d::~Vector2d()
{
}

Vector2d operator+(const Vector2d &v1, const Vector2d &v2)
{
	return Vector2d(v1.x + v2.x, v1.y + v2.y); 
}
Vector2d operator-(const Vector2d &v1, const Vector2d &v2)
{
	return Vector2d(v1.x - v2.x, v1.y - v2.y);
}
Vector2d Vector2d::operator=(const Vector2d &v)
{
	return Vector2d(v.x, v.y);
}
Vector2d::Vector2d(const Vector2d& vSource)
: x(component[0]), y(component[1])
{
	this->x = vSource.x;
	this->y = vSource.y;
}