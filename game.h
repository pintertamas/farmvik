//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

int init();
void doRender();
SDL_Texture *loadTexture(char *path);
int goods();
enum Hasznalat;
int buttonbuy(enum Hasznalat transaction);
void planting();
void bed(int x, int y, int i);

#endif //FARMVILLE2_GAME_H
