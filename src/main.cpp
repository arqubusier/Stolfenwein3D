#include <iostream>
#include <SDL.h>
#undef main
#include "vector2d.h"

using namespace std;
void CalcPos(float forw, float right, float heading);
int main()
{
	//The window we'll be rendering to 
	SDL_Window* window = NULL; 

	//The surface contained by the window 
	SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN); 

		if (window == NULL) 
		{ 
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); 
		}
	}

	vector2d inputMove;

	//Main loop flag 
	bool quit = false; 
	//Event handler 
	SDL_Event e;
	while (!quit)
	{
		inputMove.x = 0;
		inputMove.y = 0;

		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
				quit = true;

			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					inputMove.y++;
					break;
				case SDL_SCANCODE_A:
					inputMove.x--;
					break;
				case SDL_SCANCODE_S:
					inputMove.y--;
					break;
				case SDL_SCANCODE_D:
					inputMove.x++;
					break;
				}
			}
		}
	}
	SDL_Quit();
    return 0;
}

void CalcDeltaPos(vector2d inputMove, float heading)
{
	vector2d deltaPos;
	float direction = atan(inputMove.y / inputMove.x);

	heading += direction;

	float speedFactor = sqrt(pow(inputMove.x, 2)*pow(inputMove.y, 2));
	if (speedFactor > 1)
		speedFactor = 1;

	deltaPos.x = cos(heading) * speedFactor;
	deltaPos.y = sin(heading) * speedFactor;

}
