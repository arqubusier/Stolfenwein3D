#include <iostream>
#include <SDL.h>
#include "cleanup.h"

#undef main

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg);
int init_graphics(SDL_Window *win, SDL_Renderer *ren);

int main()
{
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    init_graphics(win, ren);
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

/**
 * Creates a window and a renderer
 */
int init_graphics(SDL_Window *win, SDL_Renderer *ren){
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
    
    return 0;
}
