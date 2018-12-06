//
// Created by Tomi on 2018-12-04.
//

#include "global.h"
#include "fields.h"

void resetFieldData(Field *field)
{
    field->timePlanted = 0;
    field->type = pt_APPLE;
    field->age = a_PLAIN;
    field->index = DIRT;
}

void setupFields(int column, int row)
{
    fields = (Field**)malloc(column*sizeof(Field*));
    if(fields != NULL)
    {
        for(int i=0;i<column;i++)
            fields[i] = (Field*)malloc(row*sizeof(Field));

        int width = (int)round(agyas*SCREEN_WIDTH);

        for(int i=0;i<column;i++)
        {
            for(int j=0;j<row;j++)
            {
                fields[i][j].x = 2*d + i * width;
                fields[i][j].y = 7*d + j * width;
                fields[i][j].w = width;
                resetFieldData(&fields[i][j]);
            }
        }

        columns = column;
        rows = row;
    } else {
        rows = columns = 0;
        printf("Couldn't allocate memory for fields in setupFields!\n");
    }
}

void addColumn()
{
    Field **new_fields = (Field**)malloc((columns+1)*sizeof(Field*));
    if(new_fields != NULL)
    {
        for(int i=0;i<(columns+1);i++)
            new_fields[i] = (Field*)malloc(rows*sizeof(Field));

        for(int i=0;i<columns;i++)
            for(int j=0;j<rows;j++)
                new_fields[i][j] = fields[i][j];

        int width = (int)round(agyas*SCREEN_WIDTH);

        for(int j=0;j<rows;j++)
        {
            new_fields[columns][j].x = 2*d + columns * width;
            new_fields[columns][j].y = 7*d + j * width;
            new_fields[columns][j].w = width;
            resetFieldData(&new_fields[columns][j]);
        }

        freeFields();
        fields = new_fields;
        columns++;
    } else {
        printf("Couldn't allocate memory for fields in addColumn!\n");
    }
}

bool isOverField(Field actual)
{
    if(mouseX > actual.x && mouseX < actual.x + actual.w && mouseY > actual.y && mouseY < actual.y + actual.w)
        return true;
    else
        return false;
}

void bed(Field *field, PlantType type)
{
    field->type = type;
    field->timePlanted = time(0);
}

void growField(Field *field)
{
    if( field->timePlanted != 0 ) {
        if(field->age == a_PLAIN)
            field->age = a_SEED;
        else if( time(0) - field->timePlanted >= 4 && field->age == a_SEED )
            field->age = a_SPORE;
        else if( time(0) - field->timePlanted >= 8 && field->age == a_SPORE )
            field->age = a_BIG;
        else if( time(0) - field->timePlanted >= 10 && field->age == a_BIG ) //25
            field->age = a_DEAD;
    }
}

void growFields()
{
    for(int i=0;i<columns;i++)
    {
        for(int j=0;j<rows;j++)
        {
            growField(&fields[i][j]);
            switch(fields[i][j].age)
            {
                case a_PLAIN:
                    fields[i][j].index = DIRT;
                    break;
                case a_SEED:
                    fields[i][j].index = M_ALMA + fields[i][j].type;
                    break;
                case a_SPORE:
                    fields[i][j].index = CS_ALMA + fields[i][j].type;
                    break;
                case a_BIG:
                    fields[i][j].index = N_ALMA + fields[i][j].type;
                    break;
                case a_DEAD:
                    fields[i][j].index = TOMBSTONE;
                    break;
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
    for(int i=0;i<columns;i++)
        for(int j=0;j<rows;j++)
            renderField(fields[i][j]);
}

void freeFields()
{
    for(int i=0;i<columns;i++)
        free(fields[i]);
    free(fields);
}