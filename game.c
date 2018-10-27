//
// Created by Tomi on 26/10/2018.
//

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "global.h"

int game( int argc, char *argv[] ) {

    // Initializing everything, setting up the playground

    SDL_Init( SDL_INIT_EVERYTHING );

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // creating the window

    SDL_Window *window = SDL_CreateWindow( "Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN );

    if( NULL == window )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // creating the renderer

    SDL_Renderer *renderer = SDL_CreateRenderer( window, -1, 0 );

    if( NULL == renderer )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // setting up background color

    SDL_SetRenderDrawColor( renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    SDL_RenderClear( renderer );

    SDL_RenderPresent( renderer );

    // Exiting the window

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