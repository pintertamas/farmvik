//
// Created by Tomi on 23/10/2018.
//

#ifndef FARMVILLE2_GLOBAL_H
#define FARMVILLE2_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

extern int const SCREEN_WIDTH;
extern int const SCREEN_HEIGHT;
int d;
extern int times[6];
bool player;
typedef enum Players {ONE,TWO}Players;

typedef struct Mezo{
    int type;
    int size;
}Mezo;

Mezo hely[6];
extern int money;
extern int apple;
extern int potato;
extern int tomato;
int buy_price[3];
int sell_price[3];
extern double agyas;
SDL_Event windowEvent;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textures[12];
SDL_Texture *icon_textures[4];
SDL_Texture *mag_textures[3];
SDL_Texture *csira_textures[3];
SDL_Texture *nagy_textures[3];
SDL_Surface *balance;
TTF_Font *font;
SDL_Event clickevent;
SDL_Color bggreen;

#endif //FARMVILLE2_GLOBAL_H