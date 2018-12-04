//
// Created by Tomi on 2018-12-04.
//

#ifndef FARMVILLE2_FIELDS_H
#define FARMVILLE2_FIELDS_H

#include "textures.h"

typedef enum Age{a_PLAIN,a_SEED,a_SPORE,a_BIG,a_DEAD}Age;
typedef enum PlantType{pt_APPLE,pt_POTATO,pt_TOMATO}PlantType;

typedef struct Field{
    int x, y;
    int w;
    int timePlanted;
    PlantType type;
    Age age;
    textureIndex index;
}Field;


Field **fields;
int rows, columns;

void setupFields(int column, int row);
void addColumn();
bool isOverField(Field actual);
void bed(Field *field, PlantType type);
void growFields();
void renderFields();
void freeFields();

#endif //FARMVILLE2_FIELDS_H