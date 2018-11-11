#include "global.h"
#include "game.h"
#include "farm.h"
#include "textures.h"

int main( int argc, char **argv ) {

    init(); // inicializalas
    loadImage(); // kepek betoltese memoriaba

    // Exiting the window

    bool running = true;

    while( running )
    {
        scan();
        doRender(); // renderelek mindent
        score(); // a penz es a takarmanyok kiirasa
        planting(); // mit es hova akarok ultetni?
        send();

        SDL_RenderPresent(renderer);
        //SDL_Delay(10); // fps problemak miatt

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