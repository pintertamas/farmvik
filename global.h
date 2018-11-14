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
extern int places[2][3];
int a,a_magassag,b,b_magassag,c,c_magassag,d,d_magassag,e,e_magassag,f,f_magassag;
int allapot[6][2][3];
extern int money;
extern int apple;
extern int potato;
extern int tomato;
int buy_price[3];
int sell_price[3];
int buttonx;
int buttony;
extern double agyas;
enum Hasznalat{BUY,SELL};
SDL_Event windowEvent;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *textures[8];
SDL_Texture *icon_textures[4];
SDL_Texture *mag_textures[3];
SDL_Texture *csira_textures[3];
SDL_Texture *nagy_textures[3];
SDL_Surface *balance;
TTF_Font *font;
SDL_Event clickevent;

#endif //FARMVILLE2_GLOBAL_H
