//
// Created by Tomi on 23/10/2018.
//

#include "global.h"

int const SCREEN_WIDTH = 1440;
int const SCREEN_HEIGHT = 900;
int times[6] = {0};
bool player = true;
int money;
int apple;
int potato;
int tomato;
int buy_price[3] = {20, 15, 40};
int sell_price[3] = {250, 100, 330};
double agyas = 0.15; // az ágyások szélessége es magassága SCREEN_WIDTH-tel osztva
SDL_Color bggreen = {76, 175, 80, 255};