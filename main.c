#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "global.h"

int main( int argc, char *argv[] ) {

    SDL_Init( SDL_INIT_EVERYTHING );

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: " );
        printf( SDL_GetError( ) );
    }

    SDL_Window *window = SDL_CreateWindow( "Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );

    if( NULL == window )
    {
        printf( "Error: " );
        printf( SDL_GetError( ) );

        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );

    SDL_SetRenderDrawColor( renderer, 100, 200, 55, 155 );

    SDL_RenderClear( renderer );

    SDL_RenderPresent( renderer );

    SDL_Delay(1000);

    SDL_Event windowEvent;

    bool running = true;

    while( running )
    {
        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }








    return EXIT_SUCCESS;
}