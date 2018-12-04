#include "global.h"
#include "game.h"
#include "textures.h"
#include "elements.h"

int main( int argc, char **argv ) {

    d = SCREEN_WIDTH/50;

    init(); // inicializalas
    loadImage(); // kepek betoltese memoriaba
    setupElements();
    scan(ONE); // adatok beolvasása

    bool running = true;

    while( running )
    {
        SDL_RenderClear(renderer);

        background();
        renderState();
        doRender(); // renderelek mindent
        score(); // a pénz és a takarmányok kiírasa
        planting(); // mit es hova akarok ultetni?
        timePassed();


        SDL_RenderPresent(renderer);
        //SDL_Delay(10); // fps problémák miatt

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                if(player == true)
                    send(ONE); // adatok kiírása .txt-be
                else
                    send(TWO);
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