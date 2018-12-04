//
// Created by Tomi on 26/10/2018.
//

#ifndef FARMVILLE2_GAME_H
#define FARMVILLE2_GAME_H

#include "global.h"

SDL_Window *window;
void scan(Players players);
void send(Players players);
void reset();
int init();
void timePassed();
int plantnumber();
void eventHandler();
void planting();

#endif //FARMVILLE2_GAME_H