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
    et_HARVEST, et_RESET, et_CHANGE, et_DESTROY, et_MOVE,
    STATIC
}ElementType;

typedef struct Element{
    int x, y;
    int w, h;
    ElementType e_type;
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