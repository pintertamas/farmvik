//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

SDL_Window *window;
void scan(Players players);
void save(Players players);
void reset();
int init();
void eventHandler(SDL_Event event, Players *player);

#endif //FARMVILLE2_GAME_H