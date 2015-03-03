#include "Map.h"


Map::Map()
{
	bitMapMap = SDL_LoadBMP("map.bmp");
	if (SDL_MUSTLOCK(bitMapMap))
		SDL_LockSurface(bitMapMap);

	//Fill grid with zeroes
	for (int x = 0; x < MaxX; ++x)
	{
		for (int y = 0; y < MaxY; ++y)
		{
			grid[y][x] = !GetPixel8(bitMapMap, x, y);
		}
	}
	int stop(0);
}

Map::~Map()
{

}

float Map::RayTracer(Vector2d start, float angle, Vector2d& hitPos)
{
	int x = (int)start.x, y = (int)start.y;

	angle = mod(angle, float(2*M_PI));

	int stepX(0), stepY(0);

	if (M_PI / 2 < angle && angle < 1.5 * M_PI)
		stepX = -1;
	else if (angle == M_PI / 2 || angle == 1.5 * M_PI)
		stepX = 0;
	else
		stepX = 1;

	if (0 < angle && angle < M_PI)
		stepY = 1;
	else if (angle == 0 || angle == M_PI)
		stepY = 0;
	else
		stepY = -1;


	Vector2d tMax;
	if (stepX < 0)
		tMax.x = (x - start.x) / cos(angle);
	else if (stepX > 0)
		tMax.x = (x + 1 - start.x) / cos(angle);
	else
		tMax.x = 0;

	if (stepY < 0)
		tMax.y = (y - start.y) / sin(angle);
	else if (stepY > 0)
		tMax.y = (y + 1 - start.y) / sin(angle);
	else
		tMax.y = 0;


	float k = tan(angle);
	Vector2d tDelta;
	tDelta.x = 1 / cos(angle);
	tDelta.y = 1 / sin(angle);



	while 
	(
		0 <= x && 
		x < MaxX && 
		0 <= y && 
		y < MaxY && 
		grid[x][y] == 0
	)
	{
		if (tMax.x < tMax.y)
		{
			tMax.x += tDelta.x * stepX;
			x += stepX;
		}
		else
		{
			tMax.y += tDelta.y * stepY;
			y += stepY;
		}
	}

	hitPos = { float(x), float(y) };

    //Distance to first wall hit
    if (tMax.x < tMax.y)
    {
        return tMax.x;
    }
    else
    {
        return tMax.y;
    }


}

float Map::mod(float x, float m)
{
	return fmod((fmod(x, m) + m), m);
}


Uint8 Map::GetPixel8(SDL_Surface* surface, int x, int y)
{
	//Convert the pixels to 32 bit
	Uint8* pixels = (Uint8*)surface->pixels;

	//Get the requested pixel
	return pixels[(y * surface->w) + x];
}
