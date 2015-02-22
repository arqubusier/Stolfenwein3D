#include <iostream>
#include <SDL.h>
#include <string>

//Needed for visual studio linker to work
#undef main

#include "vector2d.h"
#include "cleanup.h"

using namespace std;

typedef unsigned char byte;
struct color{
    byte r;
    byte g;
    byte b;
};

typedef struct color color;

const color BACKGROUND_COLOR = {64, 64, 64};
const color WALL_COLOR = {224, 224, 224};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Functions
void CalcDeltaPos(vector2d inputMove, float heading);
void logSDLError(std::ostream &os, const std::string &msg);
void renderColumn(SDL_Renderer *ren, int x, const int center, const int height,
        const color column_color);

int main()
{
    //init
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cout, "SDL_Init");
	    return 1;
    }

    win = SDL_CreateWindow("Stolfenwein3D", 100, 100, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (win == nullptr){
        logSDLError(std::cout, "CreateWindow");
    	SDL_Quit();
    	return 1;
    }

    ren = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr){
        logSDLError(std::cout, "CreateRenderer");
    	cleanup(win);
    	SDL_Quit();
		return 1;
	}

    //Graphics
    SDL_SetRenderDrawColor(ren, 64, 64, 64, 255);
    SDL_RenderClear(ren);

    renderColumn(ren, 10, 240, 100, WALL_COLOR);
    renderColumn(ren, 20, 240, 50, WALL_COLOR);
    renderColumn(ren, 30, 25, 50, WALL_COLOR);
     
    SDL_RenderPresent(ren);



	vector2d inputMove;

	//Event handler 
	SDL_Event event;

	//Main loop flag 
	bool quit = false;
	while (!quit)
	{
		//Reset every loop
		inputMove.x = 0;
		inputMove.y = 0;

		while (SDL_PollEvent(&event) != 0)
		{
			//User requests quit
			if (event.type == SDL_QUIT)
				quit = true;

			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
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
				case SDL_SCANCODE_LEFT:
					break;
				case SDL_SCANCODE_RIGHT:
					break;
				}
			}
		}
	}
	//cleanup
	cleanup(win, ren);
	SDL_Quit();
    return 0;
}

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void renderColumn(SDL_Renderer *ren, int x, const int center, const int height,
        const color column_color){
    SDL_SetRenderDrawColor(ren, column_color.r, column_color.g,
            column_color.b, 255);
    SDL_RenderDrawLine(ren, x, center + height/2, x, center - height/2);
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