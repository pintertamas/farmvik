//
// Created by Tomi on 04/12/2018.
//

#ifndef FARMVILLE2_ELEMENTS_H
#define FARMVILLE2_ELEMENTS_H

#include "global.h"
#include "textures.h"

typedef enum ElementType{
    SELL1, SELL2, SELL3,
    BUY1, BUY2, BUY3,
    STATIC
}ElementType;

typedef struct Element{
    int x, y;
    int w, h;
    textureIndex index;
}Element;

Element buy[3];
Element sell[3];
Element goods[3];
Element harvest;
Element resetButton;
Element change;
Element destroy;

bool isOverElement(Element actual);
void setupElements();
void renderElements();

#endif //FARMVILLE2_ELEMENTS_H