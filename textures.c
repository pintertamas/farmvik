//
// Created by Tomi on 27/10/2018.
//

#include "textures.h"
#include "global.h"
#include "farm.h"
#include "game.h"

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
    textures[6] = loadTexture("Textures/tomato.png");
    textures[7] = loadTexture("Textures/buy.png");
    textures[8] = loadTexture("Textures/sell.png");
    textures[9] = loadTexture("Textures/blank.png");
    textures[10] = loadTexture("Textures/alma_mag.png");
    textures[11] = loadTexture("Textures/alma_csira.png");
    textures[12] = loadTexture("Textures/alma_nagy.png");
    textures[13] = loadTexture("Textures/krumpli_mag.png");
    textures[14] = loadTexture("Textures/krumpli_csira.png");
    textures[15] = loadTexture("Textures/krumpli_nagy.png");
    textures[16] = loadTexture("Textures/paradicsom_mag.png");
    textures[17] = loadTexture("Textures/paradicsom_csira.png");
    textures[18] = loadTexture("Textures/paradicsom_nagy.png");


}

void doRender()
{
    int NUMBER_OF_IMAGES = 3;
    //set the drawing color to green
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);

    //clear the screen to the selected color
    SDL_RenderClear(renderer);

    //set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // setting up the design
    int margo = (int)round((double)SCREEN_WIDTH / 50);
    int fejlec = (int)round((double)SCREEN_WIDTH / 10);
    int buttonh = margo;
    int buttonw = (int)round((double)SCREEN_WIDTH / 20);

    // logo
    SDL_Rect logo = { SCREEN_WIDTH / 2 - SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[0], NULL, &logo);

    SDL_Rect logobal = { SCREEN_WIDTH / 2 - 3*SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[1], NULL, &logobal);

    SDL_Rect logojobb = { SCREEN_WIDTH / 2 + SCREEN_WIDTH / 20, 0, SCREEN_WIDTH / 10, SCREEN_WIDTH / 10 };
    SDL_RenderCopy(renderer, textures[2], NULL, &logojobb);

    // bal oldali kis ikonok és a pénz jobb oldalon
    for(int i=0;i<NUMBER_OF_IMAGES;i++)
    {
        SDL_Rect icon = { SCREEN_WIDTH / 50, (i+1)*SCREEN_WIDTH / 50 , SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 };
        SDL_RenderCopy(renderer, textures[i+4], NULL, &icon);
    }
    // jobb oldalon a pénz ikon
    SDL_Rect coin = { 3*SCREEN_WIDTH / 4, SCREEN_WIDTH / 50 , SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 };
    SDL_RenderCopy(renderer, textures[3], NULL, &coin);

    // ikonok a boltban
    for(int i=0; i<NUMBER_OF_IMAGES; i++)
    {
        SDL_Rect shop = { 3*SCREEN_WIDTH / 4 + SCREEN_WIDTH / 50, 2*(i+1)*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 10 , SCREEN_WIDTH / 30, SCREEN_WIDTH / 30 };
        SDL_RenderCopy(renderer, textures[i+4], NULL, &shop);

        SDL_Rect shoprect = { 3*SCREEN_WIDTH / 4 + SCREEN_WIDTH / 50, 2*(i+1)*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 10 , SCREEN_WIDTH / 30, SCREEN_WIDTH / 30 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &shoprect);
    }

    // a nagy negyzet az egesz cucc kozepen meg a jobb oldali
    SDL_Rect bigrect = { SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 + SCREEN_WIDTH / 10, 3*SCREEN_WIDTH / 4 - 2*SCREEN_WIDTH / 50, SCREEN_HEIGHT - 2*SCREEN_WIDTH / 50 - SCREEN_WIDTH / 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &bigrect);

    SDL_Rect smallrect = { 3*SCREEN_WIDTH / 4, SCREEN_WIDTH / 10 + SCREEN_WIDTH / 50, SCREEN_WIDTH / 4 - SCREEN_WIDTH / 50, SCREEN_HEIGHT - SCREEN_WIDTH / 10 - 2*SCREEN_WIDTH / 50 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &smallrect);

    // gombok grafikus megjelenitese

    for(int i=0; i<NUMBER_OF_IMAGES;i++)
    {
        SDL_Rect rectbuy = { 3*SCREEN_WIDTH / 4 + 3*margo + margo / 2, fejlec + 2*(i+1)*margo + SCREEN_WIDTH / 120, buttonw, buttonh };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, textures[7], NULL, &rectbuy);

        SDL_Rect rectsell = { 3*SCREEN_WIDTH / 4 + 4*margo + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100, SCREEN_WIDTH / 10 + 2*(i+1)*SCREEN_WIDTH / 50 + SCREEN_WIDTH / 120, buttonw, buttonh };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, textures[8], NULL, &rectsell);
    }
}

void score()
{
    font = TTF_OpenFont("Prototype.ttf", 25);

    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    SDL_Color black = { 255, 255, 255 };
    char buffer[50];
    sprintf(buffer, "%d arany", money);

    balance = TTF_RenderText_Solid(font, buffer, black);
    txt = SDL_CreateTextureFromSurface(renderer, balance);
    SDL_Rect box = { 3*SCREEN_WIDTH / 4 + 2*SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 , 3*SCREEN_WIDTH / 50, SCREEN_WIDTH / 50 };
    SDL_RenderCopy(renderer, txt, NULL, &box);
    SDL_FreeSurface(balance);
    SDL_RenderPresent(renderer);
}

void bed(int x, int y, int i)
{
    //(int)round((double)agyas) * SCREEN_WIDTH
    SDL_Rect rect = { x, y, (int)(agyas*SCREEN_WIDTH), (int)(agyas*SCREEN_WIDTH) };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderCopy(renderer, textures[i], NULL, &rect);
    //SDL_RenderPresent(renderer);

}