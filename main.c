#include "global.h"
#include "game.h"
#include "textures.h"

int main( int argc, char **argv ) {

    menu();
    init(); // inicializalas
    loadImage(); // kepek betoltese memoriaba

    bool running = true;

    while( running )
    {
        scan(); // adatok beolvasása
        doRender(); // renderelek mindent
        score(); // a pénz és a takarmányok kiírasa
        planting(); // mit es hova akarok ultetni?
        send(); // adatok kiírása .txt-be

        SDL_RenderPresent(renderer);
        //SDL_Delay(10); // fps problémák miatt

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
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