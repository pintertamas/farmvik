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

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    // creating the window

    window = SDL_CreateWindow( "Farmville", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( NULL == window )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        success = false;
        return success;
    }

    // creating the renderer

    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( NULL == renderer )
    {
        printf( "Error: %s\n", SDL_GetError( ) );
        success = false;
        return success;
    }

    // setting up background color

    SDL_SetRenderDrawColor( renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    return success;
}

void doRender()
{
    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);

    //Clear the screen
    SDL_RenderClear(renderer);

    //set the drawing color to green
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    int negyzet[3] = {1,30,50};

    for(int i=0;i<3;i++)
    {
        SDL_Texture *textures[NUMBER_OF_IMAGES];

        SDL_Rect rect = { 10*negyzet[i] + SCREEN_WIDTH/2 / 10, 10 + SCREEN_HEIGHT / 10, SCREEN_WIDTH / 20, SCREEN_WIDTH / 20 };
        SDL_RenderCopy(renderer, textures[i], NULL, &rect);
        //SDL_RenderFillRect(renderer, &rect);
    }

    //We are done drawing, "present" or show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}