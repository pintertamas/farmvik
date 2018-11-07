//
// Created by Tomi on 27/10/2018.
//

#include "textures.h"
#include "global.h"
#include "farm.h"

// initializing pictures

SDL_Texture *loadTexture(char *path) {

    SDL_Texture *texture = NULL;

    SDL_Surface *image = IMG_Load(path);

    if( NULL == image )
    {
        printf( "Error1: %s\n", SDL_GetError( ) );
    } else {

        texture = SDL_CreateTextureFromSurface(renderer, image);

        if( NULL == texture )
        {
            printf( "Error2: %s\n", SDL_GetError( ) );
        }
        SDL_FreeSurface(image);
    }
    return texture;
}

void loadImage() // ÚJABB KÉP FELTÖLTÉSE UTÁN A TÖMB MÉRETÉT IS NÖVELNI KELL A global.h-BAN ÉS A global.c-BEN IS!
{
    textures[0] = loadTexture("Textures/logo_300x300.png");
    textures[1] = loadTexture("Textures/logo_bal.png");
    textures[2] = loadTexture("Textures/logo_jobb.png");
    textures[3] = loadTexture("Textures/coin.png");
    textures[4] = loadTexture("Textures/apple.png");
    textures[5] = loadTexture("Textures/potato.png");


}

void doRender()
{
    //set the drawing color to green
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);

    //Clear the screen
    SDL_RenderClear(renderer);

    //set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* Ctrl + C; Ctrl + V;
    SDL_Rect valami = { SCREEN_WIDTH, SCREEN_HEIGHT, 100, 100 };
    SDL_RenderCopy(renderer, textures[X], NULL, &valami);
     */

    // setting up the design

    // logo
    SDL_Rect logo = { SCREEN_WIDTH / 2 - SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[0], NULL, &logo);

    SDL_Rect logobal = { SCREEN_WIDTH / 2 - 3*SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[1], NULL, &logobal);

    SDL_Rect logojobb = { SCREEN_WIDTH / 2 + SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[2], NULL, &logojobb);

    // the small icons on the right
    SDL_Rect coin = { SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 , SCREEN_WIDTH / 100, SCREEN_WIDTH / 100 };
    SDL_RenderCopy(renderer, textures[3], NULL, &coin);

    SDL_Rect apple = { SCREEN_WIDTH / 50, 2*SCREEN_WIDTH / 50 , SCREEN_WIDTH / 100, SCREEN_WIDTH / 100 };
    SDL_RenderCopy(renderer, textures[4], NULL, &apple);

    SDL_Rect potato = { SCREEN_WIDTH / 50, 3*SCREEN_WIDTH / 50 , SCREEN_WIDTH / 100, SCREEN_WIDTH / 100 };
    SDL_RenderCopy(renderer, textures[5], NULL, &potato);

    // a nagy negyzet az egesz cucc kozepen meg a jobb oldali
    SDL_Rect bigrect = { SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 + SCREEN_WIDTH / 10, 3*SCREEN_WIDTH / 4 - 2*SCREEN_WIDTH / 50, SCREEN_HEIGHT - 2*SCREEN_WIDTH / 50 - SCREEN_WIDTH / 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &bigrect);

    SDL_Rect smallrect = { 3*SCREEN_WIDTH / 4, SCREEN_WIDTH / 10 + SCREEN_WIDTH / 50, SCREEN_WIDTH / 4 - SCREEN_WIDTH / 50, SCREEN_HEIGHT - SCREEN_WIDTH / 10 - 2*SCREEN_WIDTH / 50 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &smallrect);

    //We are done drawing, "present" or show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}

















/*bool loadMedia()
{


    //Loading success flag
    bool success = true;

    //Load splash image
    imageSurface = SDL_LoadBMP( "demo.bmp" );
    if( imageSurface == NULL )
    {
        printf( "Error: %s\n%s", "demo.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}*/

/*void destroy_everything(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    for(int i=0; i<3; i++)
    {
        SDL_DestroyTexture(textures[i]);
        textures[i] = NULL;
    }

}*/