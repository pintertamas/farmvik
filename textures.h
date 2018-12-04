//
// Created by Tomi on 27/10/2018.
//

#ifndef FARMVILLE2_TEXTURES_H
#define FARMVILLE2_TEXTURES_H

#include "global.h"

SDL_Texture *textures[12];
SDL_Texture *icon_textures[4];
SDL_Texture *mag_textures[3];
SDL_Texture *csira_textures[3];
SDL_Texture *nagy_textures[3];
SDL_Surface *balance;
TTF_Font *font;
SDL_Texture *loadTexture(char *path);
void loadImage();
void background();
void doRender();
void score();
void renderState();
void bed(int x, int y, int i, int t);

#endif //FARMVILLE2_TEXTURES_H