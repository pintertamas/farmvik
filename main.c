#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "global.h"

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 100, 200, 55, 155);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    bool running = true;

    SDL_Event event;

    while( running )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }









    return 0;
}