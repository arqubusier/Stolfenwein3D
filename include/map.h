#ifndef Map_H
#define Map_H
#include "Vector2d.h"
#define _USE_MATH_DEFINES

#include "math.h"

class Map
{
public:
	Map();
	~Map();
	static const int MaxX = 100, MaxY = 100;

	bool grid[MaxX][MaxY];

	Vector2d RayTracer(Vector2d start, float angle);
	float mod(float x, float m);
private:
};
#endif
