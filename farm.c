//
// Created by Tomi on 26/10/2018.
//

#include "farm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Termeny {
    int posx;  // x pozíció
    int posy; // y pozíció
    int dev; // fejlettség
    bool isAlive; // életben van-e még, vagy már elrohadt
}Termeny;

int farm(){

    Termeny kukorica;
    kukorica.posx = 0;
    kukorica.posy = 0;
    kukorica.dev = 2;
    kukorica.isAlive = true;

    return 0;
}