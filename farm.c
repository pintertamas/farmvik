//
// Created by Tomi on 26/10/2018.
//

#include "farm.h"
#include "global.h"

typedef struct Termeny {
    int posx;  // x pozíció
    int posy; // y pozíció
    int dev; // fejlettség
    int age;
    bool isAlive; // életben van-e még, vagy már elrohadt
    int sorszam;
}Termeny;

void delay(int seconds)
{
    // Converting time into ms
    int ms = 1000 * seconds;

    // Start time
    clock_t start_time = clock();

    // looping until required time is not achieved
    while (clock() < start_time + ms);
}

int elultet(Termeny kukorica)
{
    int passedTime = 0;
    kukorica.dev = 0;
    kukorica.age = 0;

    delay(10);

    /*if(SDL_TICKS_PASSED(first_tick, SDL_GetTicks()) >= 1)
        kukorica.dev++;
*/
    if(kukorica.dev >= 4)
        kukorica.isAlive = false;

}

int farm(){

    Termeny kukorica;
    kukorica.posx = 0;
    kukorica.posy = 0;
    kukorica.dev = 2;
    kukorica.age = 0;
    kukorica.isAlive = true;
    kukorica.sorszam = 0;

    return 0;
}