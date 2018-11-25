//
// Created by Tomi on 27/10/2018.
//

#ifndef FARMVILLE2_TEXTURES_H
#define FARMVILLE2_TEXTURES_H

#include "global.h"

SDL_Texture *loadTexture(char *path);
void loadImage();
void background();
void doRender();
void score();
void renderState();
void bed(int x, int y, int i, int t);

#endif //FARMVILLE2_TEXTURES_H
