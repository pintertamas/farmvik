//
// Created by Tomi on 26/10/2018.
//

#include "game.h"
#include "global.h"

int init() {

    // Initializing everything, setting up the playground

    SDL_Init( SDL_INIT_EVERYTHING );

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // creating the window

    window = SDL_CreateWindow( "Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN );

    if( NULL == window )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // creating the renderer

    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( NULL == renderer )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // setting up background color

    SDL_SetRenderDrawColor( renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    return EXIT_SUCCESS;
}