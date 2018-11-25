#include "global.h"
#include "game.h"
#include "textures.h"
#include "farm.h"

int main( int argc, char **argv ) {

    init(); // inicializalas
    loadImage(); // kepek betoltese memoriaba
    scan(); // adatok beolvasása

    bool running = true;

    while( running )
    {
        SDL_RenderClear(renderer);

        background();
        renderState();
        doRender(); // renderelek mindent
        score(); // a pénz és a takarmányok kiírasa
        planting(); // mit es hova akarok ultetni?


        SDL_RenderPresent(renderer);
        //SDL_Delay(10); // fps problémák miatt

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                if(player == true)
                    send(); // adatok kiírása .txt-be
                else
                    sendPlayer2();
                running = false;
                break;
            }
        }
    }

    // Close and destroy the window and the renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();

    return 0;
}