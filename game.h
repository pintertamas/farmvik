//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

int init();
void doRender(SDL_Renderer *renderer);
int processEvents(SDL_Window *window);
SDL_Texture *loadTexture(char *path);

#endif //FARMVILLE2_GAME_H
