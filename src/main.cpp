#include <iostream>
#include <SDL.h>
#include "cleanup.h"

//Needed for visual studio linker to work
#undef main

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg);

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
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderDrawLine(ren, 10, 10, 100, 100);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

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
