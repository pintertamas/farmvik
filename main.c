
#include "global.h"
#include "game.h"
#include "farm.h"

int main( int argc, char **argv ) {

    init();

    // Exiting the window

    bool running = true;

    while( running )
    {
        SDL_RenderClear( renderer );

        SDL_RenderPresent( renderer );

        while( SDL_PollEvent( &windowEvent ) != 0 )
        {
            if( windowEvent.type == SDL_QUIT )
            {
                running = false;
                break;
            }
        }
    }

    return 0;
}