//
// Created by Tomi on 13/11/2018.
//

#include "global.h"
#include "menu.h"

int menuclick(bool running)
{
    SDL_Event menuclickevent;
    bool click = false;
    int menud = 640 / 6; // 106, csak így jobban látszik az arány
    int menubuttonx = -1;
    int menubuttony = -1;

    SDL_WaitEvent(&menuclickevent);

    switch(menuclickevent.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (menuclickevent.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(menuclickevent.button.x != -1 && menuclickevent.button.y != -1)
                {
                    menubuttonx = menuclickevent.button.x;
                    menubuttony = menuclickevent.button.y;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (menuclickevent.button.button == SDL_BUTTON_LEFT) {
                click = false;
            }
            break;
        default:
            break;
    }

    if(click == true)
    {
        if(menubuttonx <= 640 / 2 + menud && menubuttonx >= 640 / 2 - menud && menubuttony >= SCREEN_WIDTH / 50 && menubuttony <= SCREEN_WIDTH / 50 + d)
        {
            printf("%d %d\n", menubuttonx, menubuttony);
            return 1;
        }
        else {
        }

    }
}

int menu() {

    SDL_Window *menuwindow;
    SDL_Renderer *menurenderer;
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    menuwindow = SDL_CreateWindow( "FarmVik MENU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL );
    menurenderer = SDL_CreateRenderer( menuwindow, -1, 0 );

    if (menuwindow == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    bool running = true;

    while( running )
    {
        SDL_SetRenderDrawColor(menurenderer, 76, 175, 80, 255);
        SDL_RenderClear(menurenderer);

        menuclick(running);
        SDL_Delay(10);
        SDL_RenderPresent(menurenderer);

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    // Clean up
    SDL_Quit();
    return 0;
}