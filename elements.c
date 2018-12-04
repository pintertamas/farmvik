//
// Created by Tomi on 04/12/2018.
//

#include "elements.h"
#include "textures.h"

int mx, my;

void setMousePos(int x, int y)
{
    mx = x;
    my = y;
}

bool isOver(Element actual){
    if(mx > actual.x && mx < actual.x + actual.w && my > actual.y && my < actual.y + actual.h)
        return true;
    else
        return false;
}

void setupElements()
{
    int fejlec = (int) round((double) SCREEN_WIDTH / 10);
    int buttonw = 2*d;
    int buttonh = d;

    for(int i=0;i<3;i++) {
        buy[i].x = 3*SCREEN_WIDTH / 4 + 3*d + d / 2;
        buy[i].y = fejlec + 2*(i+1)*d + SCREEN_WIDTH / 120;
        buy[i].w = buttonw;
        buy[i].h = buttonh;
        buy[i].texture = textures[4];

        sell[i].x = 3*SCREEN_WIDTH / 4 + 4*d + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100;
        sell[i].y = fejlec + 2*(i+1)*d + SCREEN_WIDTH / 120;
        sell[i].w = buttonw;
        sell[i].h = buttonh;
        sell[i].texture = textures[5];

        goods[i].x =  3*SCREEN_WIDTH / 4 + d;
        goods[i].y = 2*(i+1)*d + SCREEN_WIDTH / 10;
        goods[i].w = SCREEN_WIDTH / 30;
        goods[i].h = SCREEN_WIDTH / 30;
        goods[i].texture = icon_textures[i+1];
    }

    //harvest button
    harvest.x = 3*SCREEN_WIDTH / 4 + 3*d;
    harvest.y = SCREEN_WIDTH / 10 + 9*d;
    harvest.w = 3*SCREEN_WIDTH/20;
    harvest.h = d;
    harvest.texture = textures[8];

    //reset button
    resetButton.x = 3*SCREEN_WIDTH / 4 + 3*d;
    resetButton.y = SCREEN_WIDTH / 10 + 11*d;
    resetButton.w = 2*d;
    resetButton.h = 2*d;
    resetButton.texture = textures[9];

    //change button
    change.x = 3*SCREEN_WIDTH / 4 + 6*d;
    change.y = SCREEN_WIDTH / 10 + 11*d;
    change.w = 2*d;
    change.h = 2*d;
    change.texture = textures[10];

    //destroy button
    destroy.x = 3*SCREEN_WIDTH / 4 + 3*d;
    destroy.y = SCREEN_WIDTH / 10 + 11*d;
    destroy.w = 3*SCREEN_WIDTH/20;
    destroy.h = d;
    destroy.texture = textures[11];
}