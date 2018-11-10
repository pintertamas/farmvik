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

int goods()
{
    bool click = false;
    int d = (int)(agyas*SCREEN_WIDTH);
    SDL_WaitEvent(&clickplant);

    switch(clickplant.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (clickplant.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(clickplant.button.x != -1 && clickplant.button.y != -1)
                {
                    buttonx = clickplant.button.x - 2*SCREEN_WIDTH / 50; // A cella fölött lévő rész mérete. Gyakorlatilag megkapom a koordinátáját a kattintásnak a cella koordinátarendszerében
                    buttony = clickplant.button.y - 7*SCREEN_WIDTH / 50; // Szintén.
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (clickplant.button.button == SDL_BUTTON_LEFT) {
                click = false;
            }
            break;
        default:
            break;
    }
    if(click == true)
        printf("%d %d\n", buttonx, buttony);

    if(click == true)
    {
        if(buttonx > 0 && buttonx < d && buttony > 0 && buttony < 3*d)
        {
            printf("%d\n", (buttony / d) + 1);
            return (buttony / d) + 1;
        }
        else if(buttonx > d && buttonx < 2*d && buttony > 0 && buttony < 3*d)
        {
            printf("%d\n", (buttony / d) + 4);
            return (buttony / d) + 4;
        }
    }
}

int buttonbuy()
{
    bool click = false;
    int d = (int)(agyas*SCREEN_WIDTH);
    SDL_WaitEvent(&clickplant);

    switch(clickplant.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (clickplant.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(clickplant.button.x != -1 && clickplant.button.y != -1)
                {
                    buttonx = clickplant.button.x - 2*SCREEN_WIDTH / 50; // A cella fölött lévő rész mérete. Gyakorlatilag megkapom a koordinátáját a kattintásnak a cella koordinátarendszerében
                    buttony = clickplant.button.y - 7*SCREEN_WIDTH / 50; // Szintén.
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (clickplant.button.button == SDL_BUTTON_LEFT) {
                click = false;
            }
            break;
        default:
            break;
    }
    if(click == true)
        printf("%d %d\n", buttonx, buttony);

    if(click == true)
    {
        if(buttonx > 0 && buttonx < d && buttony > 0 && buttony < 3*d)
        {
            printf("%d\n", (buttony / d) + 1);
            return (buttony / d) + 1;
        }
        else if(buttonx > d && buttonx < 2*d && buttony > 0 && buttony < 3*d)
        {
            printf("%d\n", (buttony / d) + 4);
            return (buttony / d) + 4;
        }
    }
}