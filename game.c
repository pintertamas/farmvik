//
// Created by Tomi on 26/10/2018.
//

#include "game.h"
#include "global.h"
#include "textures.h"

int init() {

    bool success = true;

    // Initializing everything, setting up the playground

    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    // creating the window

    window = SDL_CreateWindow( "Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( NULL == window )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }

    // creating the renderer

    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( NULL == renderer )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }

    // setting up background color

    SDL_SetRenderDrawColor( renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    return success;
}

int buttons()
{
    // ezeket majd megpróbálom globálisan eltárolni
    /*int applebuyx = 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 100;
    int applebuyy =  SCREEN_WIDTH / 10 + 2*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;
    int applesellx = 3*SCREEN_WIDTH / 4 + 4*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100;
    int appleselly = SCREEN_WIDTH / 10 + 2*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;

    int potatobuyx = 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 100;
    int potatobuyy = SCREEN_WIDTH / 10 + 4*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;
    int potatosellx = 3*SCREEN_WIDTH / 4 + 4*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100;
    int potatoselly = SCREEN_WIDTH / 10 + 4*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;

    int tomatobuyx = 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 100;
    int tomatobuyy = SCREEN_WIDTH / 10 + 6*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;
    int tomatosellx = 3*SCREEN_WIDTH / 4 + 4*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100;
    int tomatoselly = SCREEN_WIDTH / 10 + 6*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120;*/
    //


}