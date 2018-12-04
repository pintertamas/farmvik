//
// Created by Patrick on 2018-12-04.
//

#ifndef FARMVILLE2_FIELDS_H
#define FARMVILLE2_FIELDS_H

#include "textures.h"

typedef enum Age{PLAIN,SEED,SPORE,BIG,DEAD}Age;
typedef enum PlantType{t_APPLE,t_POTATO,t_TOMATO}PlantType;

typedef struct Field{
    int x, y;
    int w;
    int timePlanted;
    PlantType type;
    Age age;
    textureIndex index;
}Field;

void setupFields(int row, int column);
bool isOverField(Field actual);
void bed(Field *field, PlantType type);
void growFields();
void renderFields();
void freeFields();

#endif //FARMVILLE2_FIELDS_H
