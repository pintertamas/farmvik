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
        doRender();
        score();
        planting();

        for(int i=0;i<3;i++)
        {
            bed(2*SCREEN_WIDTH / 50, SCREEN_WIDTH / 10 + 2*SCREEN_WIDTH / 50 + (int)(i*agyas*SCREEN_WIDTH), 10+i);
        }
        for(int i=0;i<3;i++)
        {
            bed(2*SCREEN_WIDTH / 50 + (int)(agyas*SCREEN_WIDTH), SCREEN_WIDTH / 10 + 2*SCREEN_WIDTH / 50 + (int)(i*agyas*SCREEN_WIDTH), 15+i);
        }

        SDL_RenderPresent(renderer);
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

    // Close and destroy the window and the renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();

    return 0;
}