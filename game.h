//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

int menu();
void scan();
void send();
void reset();
int init();
void doRender();
SDL_Texture *loadTexture(char *path);
int goods();
int buttonEventHandler();
void planting();
void bed(int x, int y, int i);

#endif //FARMVILLE2_GAME_H
