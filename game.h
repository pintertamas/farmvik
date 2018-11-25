//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

int menu();
void scan();
void send();
void sendPlayer2();
void reset();
int init();
void doRender();
SDL_Texture *loadTexture(char *path);
int goods();
int buttonEventHandler();
void planting();

#endif //FARMVILLE2_GAME_H
