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
    textures[1] = loadTexture("Textures/logo_bal_300x300.png");
    textures[2] = loadTexture("Textures/logo_jobb_300x300.png");
    textures[3] = loadTexture("Textures/krumpli_mag_300x300.png");
    textures[4] = loadTexture("Textures/krumpli_nagy_300x300.png");

}

void doRender()
{
    //set the drawing color to green
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);

    //Clear the screen
    SDL_RenderClear(renderer);

    //set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /*int negyzet[3] = {1,30,50};

    for(int i=0;i<3;i++)
    {
        SDL_Rect rect = { 10*negyzet[i] + SCREEN_WIDTH/2 / 10, 10 + SCREEN_HEIGHT / 10, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
        SDL_RenderCopy(renderer, textures[i], NULL, &rect);
        SDL_free(&rect);
    }*/


    // setting up the design
    SDL_Rect logo = { SCREEN_WIDTH / 2 - SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[0], NULL, &logo);

    SDL_Rect logobal = { SCREEN_WIDTH / 2 - 3*SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[1], NULL, &logobal);

    SDL_Rect logojobb = { SCREEN_WIDTH / 2 + SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[2], NULL, &logojobb);


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