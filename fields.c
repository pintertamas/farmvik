//
// Created by Tomi on 2018-12-04.
//

#include "global.h"
#include "fields.h"

void resetFieldData(Field *field) { // alapártákre állítja az adott mezőt
    field->timePlanted = 0;
    field->type = pt_APPLE;
    field->age = a_PLAIN;
    field->index = DIRT;
}

void setupFields(int column, int row) {
    fields = (Field **) malloc(column * sizeof(Field *)); // lefoglalja az oszlopokat [fields]
    if (fields != NULL) {
        for (int i = 0; i < column; i++)
            fields[i] = (Field *) malloc(row * sizeof(Field)); // aztán a sorokat is [fields]

        int width = (int) round(agyas * SCREEN_WIDTH); // az agyas egy szám, ami nem tudom már miért jó, de jó.

        for (int i = 0; i < column; i++) { // végigmegy az összes mezőn és beállítja az értékeket
            for (int j = 0; j < row; j++) {
                fields[i][j].x = 2 * d + i * width;
                fields[i][j].y = 7 * d + j * width;
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

void addColumn() {
    Field **new_fields = (Field **) malloc((columns + 1) * sizeof(Field *)); // egyel szélesebb kert [new_fields]
    if (new_fields != NULL) {
        for (int i = 0; i < (columns + 1); i++)
            new_fields[i] = (Field *) malloc(rows * sizeof(Field)); // lefoglalja a sorokat is [new_fields]

        for (int i = 0; i < columns; i++)
            for (int j = 0; j < rows; j++)
                new_fields[i][j] = fields[i][j]; // az addigi állapotát a kertnek betölti az új, nagyobb kertbe [new_fields]

        int width = (int) round(agyas * SCREEN_WIDTH);

        for (int j = 0; j < rows; j++) { // az új oszlop értékeit alapártékre állítja
            new_fields[columns][j].x = 2 * d + columns * width;
            new_fields[columns][j].y = 7 * d + j * width;
            new_fields[columns][j].w = width;
            resetFieldData(&new_fields[columns][j]); // mindent nulláz az utolsó oszlopban
        }

        freeFields(); // felszabadítja a fieldset
        fields = new_fields; // aztán beadja az új kert értékeit a réginek
        columns++; // növeli az oszlopok számát
    } else {
        printf("Couldn't allocate memory for fields in addColumn!\n");
    }
}

bool isOverField(Field actual) { // felette van-e az egér a mezőnek
    if (mouseX > actual.x && mouseX < actual.x + actual.w && mouseY > actual.y && mouseY < actual.y + actual.w)
        return true;
    else
        return false;
}

void bed(Field *field, PlantType type) { // adott típus beállítása, és idő megjegyzése
    field->type = type;
    field->timePlanted = time(0);
}

void growField(Field *field) { // növeli a termény életkorát
    if (field->timePlanted != 0) {
        if (field->age == a_PLAIN)
            field->age = a_SEED;
        else if (time(0) - field->timePlanted >= 4 && field->age == a_SEED)
            field->age = a_SPORE;
        else if (time(0) - field->timePlanted >= 8 && field->age == a_SPORE)
            field->age = a_BIG;
        else if (time(0) - field->timePlanted >= 10 && field->age == a_BIG) //25
            field->age = a_DEAD;
    }
}

void growFields() { // növeli a termény méretét (azaz a textúrájának az indexét állítgatja)
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            growField(&fields[i][j]);
            switch (fields[i][j].age) {
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

void renderField(Field field) {
    SDL_Rect dest = {field.x, field.y, field.w, field.w};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderCopy(renderer, getTexture(field.index), NULL, &dest);
}

void renderFields() {
    for (int i = 0; i < columns; i++)
        for (int j = 0; j < rows; j++)
            renderField(fields[i][j]);
}

void freeFields() {
    for (int i = 0; i < columns; i++)
        free(fields[i]);
    free(fields);
}