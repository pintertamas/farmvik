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
extern int money;
extern int apple;
extern int potato;
extern int tomato;
int buttonx;
int buttony;
extern double agyas;
SDL_Event windowEvent;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textures[20];
SDL_Surface *balance;
SDL_Texture *txt;
TTF_Font *font;
SDL_Event clickbuy;
SDL_Event clicksell;
SDL_Event clickplant;

/*int applebuyx;
int applebuyy;
int applesellx;
int appleselly;

int potatobuyx;
int potatobuyy;
int potatosellx;
int potatoselly;

int tomatobuyx;
int tomatobuyy;
int tomatosellx;
int tomatoselly;*/

#endif //FARMVILLE2_GLOBAL_H
