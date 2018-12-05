#include "global.h"
#include "game.h"
#include "textures.h"
#include "elements.h"
#include "fields.h"

int main( int argc, char **argv ) {

    d = SCREEN_WIDTH/50;
    Players player = ONE;

    init(); // inicializalas
    loadImage(); // kepek betoltese memoriaba
    setupElements();
    scan(player); // adatok beolvasása

    bool running = true;

    while( running )
    {
        SDL_Event event;
        while( SDL_PollEvent( &event ) != 0 )
        {
            eventHandler(event,&player);
            if( event.type == SDL_QUIT )
            {
                save(player);
                running = false;
                break;
            }
        }

        growFields();

        SDL_RenderClear(renderer);

        background();
        doRender(); // renderelek mindent
        renderElements();
        renderFields();
        score(); // a pénz és a takarmányok kiírasa

        SDL_RenderPresent(renderer);
    }

    freeFields();

    // Close and destroy the window and the renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();

    return 0;
}