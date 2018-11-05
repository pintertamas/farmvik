#include "global.h"
#include "game.h"
#include "farm.h"
#include "textures.h"

int main( int argc, char **argv ) {

    init();
    loadImage();

    // Exiting the window

    bool running = true;

    while( running )
    {
        SDL_RenderClear( renderer );

        doRender(renderer);

        SDL_RenderPresent( renderer );

        SDL_Delay(10);

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }

    }

    // Close and destroy the window

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();

    return 0;
}