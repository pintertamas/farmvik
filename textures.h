//
// Created by Tomi on 27/10/2018.
//

#ifndef FARMVILLE2_TEXTURES_H
#define FARMVILLE2_TEXTURES_H

#include "global.h"

typedef enum textureIndex{
    LOGO, LOGO_BAL, LOGO_JOBB,
    BUY, SELL, DIRT, TOMBSTONE, HARVEST, RESET, CHANGE, DESTROY,
    COIN, APPLE, POTATO, TOMATO,
    M_ALMA, M_KRUMPLI, M_PARADICSOM,
    CS_ALMA, CS_KRUMPLI, CS_PARADICSOM,
    N_ALMA, N_KRUMPLI, N_PARADICSOM
}textureIndex;

SDL_Texture *textures[25];
SDL_Texture *icon_textures[4];
SDL_Texture *mag_textures[3];
SDL_Texture *csira_textures[3];
SDL_Texture *nagy_textures[3];
SDL_Surface *balance;
TTF_Font *font;

SDL_Texture *loadTexture(char *path);

SDL_Texture* getTexture(textureIndex index);
void loadImage();
void background();
void doRender();
void score();
//void renderState();
//void bed(int x, int y, int i, int t);

#endif //FARMVILLE2_TEXTURES_H