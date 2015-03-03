#include <iostream>
#include <SDL.h>
#include <string>

//Needed for visual studio linker to work
#undef main

#include "Vector2d.h"
#include "cleanup.h"
#include "Player.h"
#include "Map.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int HORIZON = SCREEN_HEIGHT/2;
const SDL_Color ROOF_COLOR = {64, 64, 64, 255};
const SDL_Color FLOOR_COLOR = {100, 100, 100, 255};
const SDL_Color WALL_COLOR = {224, 224, 224, 255};


//Functions
void CalcDeltaPos(Vector2d inputMove, float heading);
void logSDLError(std::ostream &os, const std::string &msg);
void renderColumn(SDL_Renderer *ren, int x, const int horizon, const int height,
        const SDL_Color column_color);
void renderBackground(SDL_Renderer *ren, const int horizon, const SDL_Color roof,
        const SDL_Color floor);
float mod(float x, float m);
float degreesToRadians(float angle);




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
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    SDL_RenderPresent(ren);
	float fov = degreesToRadians(70);
	float radiansPerPixel = fov / SCREEN_WIDTH;

    //input
	Vector2d inputMove;
	

	//Event handler 
	SDL_Event event;

	//Map
	Map map;
	
	//Player
	Player player(4, 4, degreesToRadians(45));

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
					player.heading -= 0.02f;
					break;
				case SDL_SCANCODE_RIGHT:
					player.heading += 0.02f;
					break;
				case SDL_SCANCODE_ESCAPE:
					quit = true;
					break;
				}
			}
		}

		//Render scene
		renderBackground(ren, HORIZON, ROOF_COLOR, FLOOR_COLOR);

		float rayAngle = -(fov / 2);
		for (int column = 0; column < SCREEN_WIDTH; column++)
		{
			rayAngle += radiansPerPixel;

			Vector2d hitPos; // <--Optional
			float dist = 2 * map.RayTracer(player.position, player.heading + rayAngle, hitPos) / cos(rayAngle);

			renderColumn(ren, column, HORIZON, dist, WALL_COLOR);
			
		}


		SDL_RenderPresent(ren);
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

void renderColumn(SDL_Renderer *ren, int x, const int horizon, const int height,
        const SDL_Color column_color){
    SDL_SetRenderDrawColor(ren, column_color.r, column_color.g,
            column_color.b, 255);
    SDL_RenderDrawLine(ren, x, horizon + height/2, x, horizon - height/2);
}

void renderBackground(SDL_Renderer *ren, const int horizon, const SDL_Color roof, const SDL_Color floor){
    //Render roof
    SDL_SetRenderDrawColor(ren, roof.r, roof.g, roof.b, roof.a);
    SDL_Rect area = {0, 0, SCREEN_WIDTH, horizon};
    SDL_RenderFillRect(ren, &area);
    
    //Render floor
    SDL_SetRenderDrawColor(ren, floor.r, floor.g, floor.b, floor.a);
    area.y = horizon;
    area.h = SCREEN_HEIGHT - horizon;
    SDL_RenderFillRect(ren, &area);
}

void CalcDeltaPos(Vector2d inputMove, float heading)
{
	Vector2d deltaPos;
	float direction = atan(inputMove.y / inputMove.x);

	heading += direction;

	float speedFactor = sqrt(pow(inputMove.x, 2)*pow(inputMove.y, 2));
	if (speedFactor > 1)
		speedFactor = 1;

	deltaPos.x = cos(heading) * speedFactor;
	deltaPos.y = sin(heading) * speedFactor;

}
float degreesToRadians(float angle)
{
	return (angle * M_PI) / 180;
}
