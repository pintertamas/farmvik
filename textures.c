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

//SDL_Texture *textures;

void loadImage()
{
    SDL_Texture *textures[3];
    textures[0] = loadTexture("Textures/krumpli_mag_300x300.png");
    textures[1] = loadTexture("Textures/logo_300x300.png");
    textures[2] = loadTexture("Textures/krumpli_nagy_300x300.png");
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