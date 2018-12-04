//
// Created by Tomi on 04/12/2018.
//

#include "elements.h"

int mx, my;

void setMousePos(int x, int y)
{
    mx = x;
    my = y;
}

bool isOver(Element actual)
{
    if(mx > actual.x && mx < actual.x + actual.w && my > actual.y && my < actual.y + actual.h)
        return true;
    else
        return false;
}

void setupElements()
{
    int fejlec = (int) round((double) SCREEN_WIDTH / 10);

    for(int i=0;i<3;i++) {
        buy[i].x = 3*SCREEN_WIDTH / 4 + 3*d + d / 2;
        buy[i].y = fejlec + 2*(i+1)*d + SCREEN_WIDTH / 120;
        buy[i].w = 2*d;
        buy[i].h = d;
        buy[i].index = BUY;

        sell[i].x = 3*SCREEN_WIDTH / 4 + 4*d + SCREEN_WIDTH / 20 + SCREEN_WIDTH / 100;
        sell[i].y = fejlec + 2*(i+1)*d + SCREEN_WIDTH / 120;
        sell[i].w = 2*d;
        sell[i].h = d;
        sell[i].index = SELL;

        goods[i].x =  3*SCREEN_WIDTH / 4 + d;
        goods[i].y = 2*(i+1)*d + SCREEN_WIDTH / 10;
        goods[i].w = SCREEN_WIDTH / 30;
        goods[i].h = SCREEN_WIDTH / 30;
        goods[i].index = APPLE+i;
    }

    //harvest button
    harvest.x = 3*SCREEN_WIDTH / 4 + 3*d;
    harvest.y = fejlec + 9*d;
    harvest.w = 5*d;
    harvest.h = 2*d;
    harvest.index = HARVEST;

    //reset button
    resetButton.x = 3*SCREEN_WIDTH / 4 + 3*d;
    resetButton.y = fejlec + 12*d;
    resetButton.w = 2*d;
    resetButton.h = 2*d;
    resetButton.index = RESET;

    //change button
    change.x = 3*SCREEN_WIDTH / 4 + 6*d;
    change.y = fejlec + 12*d;
    change.w = 2*d;
    change.h = 2*d;
    change.index = CHANGE;

    //destroy button
    destroy.x = 3*SCREEN_WIDTH / 4 + 3*d;
    destroy.y = fejlec + 15*d;
    destroy.w = 5*d;
    destroy.h = 2*d;
    destroy.index = DESTROY;
}

void renderElement(Element element)
{
    SDL_Rect dest = { element.x, element.y, element.w, element.h };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderCopy(renderer, getElementTexture(element.index), NULL, &dest);
}

void renderElementRect(Element element)
{
    SDL_Rect dest = { element.x, element.y, element.w, element.h };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &dest);
}

void renderElements()
{
    for(int i=0;i<3;i++) {
        renderElement(buy[i]);
        renderElement(sell[i]);
        renderElement(goods[i]);
        renderElementRect(goods[i]);
    }
    renderElement(harvest);
    renderElement(resetButton);
    renderElement(change);
    renderElement(destroy);
}