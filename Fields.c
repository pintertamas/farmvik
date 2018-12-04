//
// Created by Patrick on 2018-12-04.
//

#include "global.h"
#include "Fields.h"

Field **fields = NULL;
int rows, columns;

void setupFields(int row, int column)
{
    fields = (Field**)malloc(row*sizeof(Field));
    if(fields != NULL) {
        for(int i=0;i<row;i++)
            fields[i] = (Field*)malloc(column*sizeof(Field));

        int width = (int)round(agyas*SCREEN_WIDTH);

        for(int i=0;i<row;i++) {
            for(int j=0;j<column;j++) {
                fields[i][j].x = 2*d + i * width;
                fields[i][j].y = 7*d + j * width;
                fields[i][j].w = width;
                fields[i][j].timePlanted = 0;
                fields[i][j].type = t_APPLE;
                fields[i][j].age = PLAIN;
                fields[i][j].index = DIRT;
            }
        }

        rows = row;
        columns = column;
    } else {
        rows = columns = 0;
        printf("Couldn't allocate memory for fields!\n");
    }
}

void growField(Field *field)
{
    if( field->type != PLAIN ) {
        if( time(0) - field->timePlanted == 4 && field->age == SEED )
            field->age++;
        else if( time(0) - field->timePlanted == 8 && field->age == SPORE )
            field->age++;
        else if( time(0) - field->timePlanted >= 25 && field->age == BIG )
            field->age = DEAD;
    }
}

void growFields()
{
    for(int i=0;i<rows;i++) {
        for(int j=0;j<columns;j++) {
            growField(&fields[i][j]);
            switch(fields[i][j].type) {
                case t_APPLE:
                    fields[i][j].index =
                default:
                    fields[i][j].index = DIRT;
                    break;
            }
        }
    }
}

void renderField(Field field)
{
    SDL_Rect dest = { field.x, field.y, field.w, field.w };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderCopy(renderer, getTexture(field.index), NULL, &dest);
}

void renderFields()
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
            renderField(fields[i][j]);
}

void freeFields()
{
    for(int i=0;i<rows;i++)
        free(fields[i]);
    free(fields);
}