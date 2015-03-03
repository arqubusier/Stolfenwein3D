#ifndef Map_H
#define Map_H
#include <SDL.h>

#include "math.h"

#include "Vector2d.h"

class Map
{
public:
	Map();
	~Map();
	static const int MaxX = 100, MaxY = 100;

	SDL_Surface* bitMapMap;
	bool grid[MaxX][MaxY];

	float RayTracer(Vector2d start, float angle, Vector2d& hitPos);
private:
	float mod(float x, float m);
	Uint8 GetPixel8(SDL_Surface* surface, int x, int y);
};
#endif
