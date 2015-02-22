#ifndef Map_H
#define Map_H
#include "Vector2d.h"

class Map
{
public:
	Map();
	~Map();
	static const int MaxX = 100, MaxY = 100;

	static bool grid[MaxX][MaxY];
private:
};
#endif
