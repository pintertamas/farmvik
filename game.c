//
// Created by Tomi on 26/10/2018.
//

#include <string.h>
#include "game.h"
#include "global.h"
#include "textures.h"
#include "farm.h"

int init() {

    bool success = true;

    // Initializing everything, setting up the playground
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }
    // creating the window
    window = SDL_CreateWindow( "FarmVik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }
    // creating the renderer
    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( renderer == NULL )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }

    // setting up background color

    SDL_SetRenderDrawColor( renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    return success;
}

void scan()
{
    FILE* data;
    data = fopen("gameData.txt", "r");

    for(int i=0;i<6;i++)
        fscanf(data, "%d %d\n", &hely[i].type, &hely[i].size);

    fscanf(data, "%d\n%d %d %d", &money, &apple, &potato, &tomato);

    for(int i=0;i<6;i++)
    {
        printf("%d %d\n", hely[i].type, hely[i].size);
    }

    if (data != NULL) {
        // type (pl ha 1, akkor alma)
        // size: azt jelzi, hogy az ott lévő termény mekkora (0-4 kozott)
        // ures - mag - csira - nagy - rohadt

        fclose(data);
    } else{
        printf("Error: Could not open the file");
    }
}

void scanPlayer2()
{
    FILE* data;
    data = fopen("gameDataPlayer2.txt", "r");

    for(int i=0;i<6;i++)
    {
        fscanf(data, "%d %d\n",  &hely[i].type,  &hely[i].size);
    }
    fscanf(data, "%d\n%d %d %d", &money, &apple, &potato, &tomato);

    if (data != NULL)
    {
        fclose(data);
    } else{
        printf("Error: Could not open the file");
    }
}

void send()
{
    FILE* data;
    data = fopen("gameData.txt", "w");

    for(int i=0;i<6;i++)
    {
        fprintf(data, "%d %d\n", hely[i].type, hely[i].size);
    }
    fprintf(data, "%d\n%d %d %d", money, apple, potato, tomato);
    fclose(data);

    for(int i=0;i<6;i++)
    {
        printf("%d %d\n", hely[i].type, hely[i].size);
    }
}

void sendPlayer2()
{
    FILE* data;
    data = fopen("gameDataPlayer2.txt", "w");

    for(int i=0;i<6;i++)
    {
        fprintf(data, "%d %d\n", hely[i].type, hely[i].size);
    }
    fprintf(data, "%d\n%d %d %d", money, apple, potato, tomato);
    fclose(data);

    for(int i=0;i<6;i++)
    {
        printf("%d %d\n", hely[i].type, hely[i].size);
    }
}

void reset()
{
    FILE* data;
    data = fopen("gameDataNull.txt", "r");

    for(int i=0;i<6;i++)
    {
        fscanf(data, "%d %d\n",  &hely[i].type,  &hely[i].size);
    }
    fscanf(data, "%d\n%d %d %d", &money, &apple, &potato, &tomato);

    if (data != NULL)
    {
        fclose(data);
    } else{
        printf("Error: Could not open the file");
    }
}

int goods()
{
    bool click = false;
    int d = (int)(agyas*SCREEN_WIDTH);
    SDL_WaitEvent(&clickevent);

    switch(clickevent.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (clickevent.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(clickevent.button.x != -1 && clickevent.button.y != -1)
                {
                    buttonx = clickevent.button.x - 2*SCREEN_WIDTH / 50; // A cella fölött lévo rész mérete. Gyakorlatilag megkapom a koordinátáját a kattintásnak a cella koordinátarendszerében
                    buttony = clickevent.button.y - 7*SCREEN_WIDTH / 50; // Szintén.
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (clickevent.button.button == SDL_BUTTON_LEFT) {
                click = false;
            }
            break;
        default:
            break;
    }

    if(click == true)
    {
        if(buttonx > 0 && buttonx < d && buttony > 0 && buttony < 3*d)
        {
            //printf("%d\n", (buttony / d) + 1);
            /*if(hely[buttony / d].size == 0)
            {
                hely[buttony / d].size++;
            }*/
            return (buttony / d) + 1;
        }
        else if(buttonx > d && buttonx < 2*d && buttony > 0 && buttony < 3*d)
        {
            //printf("%d\n", (buttony / d) + 4);
            /*if(hely[buttony / d + 3].size == 0)
            {
                hely[buttony / d + 3].size++;
            }*/
            return (buttony / d) + 4;
        }
    }
    goods();
}

int buttonEventHandler()
{
    int BUTTON_HEIGHT = SCREEN_WIDTH / 50; // a gombok mérete, létrehozáskor buttonw és buttonh volt a nevük, csak név ütközés miatt most máshogy nevezem el.
    int BUTTON_WIDTH = (int)round((double)SCREEN_WIDTH / 20);
    int d = BUTTON_HEIGHT;
    bool click = false;
    SDL_WaitEvent(&clickevent);

    switch(clickevent.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (clickevent.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(clickevent.button.x != -1 && clickevent.button.y != -1)
                {
                    buttonx = clickevent.button.x - 41*SCREEN_WIDTH / 50;
                    buttony = clickevent.button.y - 7*SCREEN_WIDTH / 50 - SCREEN_WIDTH / 120;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (clickevent.button.button == SDL_BUTTON_LEFT) {
                click = false;
            }
            break;
        default:
            break;
    }

    if(click == true)
    {
        if(buttonx > 0 && buttonx < 2*BUTTON_WIDTH + SCREEN_WIDTH / 50 && buttony > 0 && buttony < SCREEN_WIDTH / 10)
        {
            for(int i=0; i<3;i++)
            {
                if (0 <= buttonx && buttonx <= BUTTON_WIDTH && (i * 2 * d) <= buttony && buttony <= d + (i * 2 * d)) {
                        //printf("%d\n", (buttony / (2 * d)) + 1);
                        return (buttony / (2 * d)) + 1; // visszaadja a vásárolni kívánt termény sorszámát
                    }

                else if ((BUTTON_WIDTH + d) <= buttonx && buttonx <= (BUTTON_WIDTH + d) + BUTTON_WIDTH && (i * 2 * d) <= buttony && buttony <= d + (i * 2 * d))
                    {
                        //printf("%d\n", (buttony / (2 * d)) + 1);

                        int selltype = ((buttony / (2 * d)) + 1);

                        if(selltype == 1 && apple > 0)
                        {
                            money += apple * sell_price[selltype - 1];
                            apple = 0;
                        }
                        else if(selltype == 2 && potato > 0)
                        {
                            money += potato * sell_price[selltype - 1];
                            potato = 0;
                        }
                        else if(selltype == 3 && tomato > 0)
                        {
                            money += tomato * sell_price[selltype - 1];
                            tomato = 0;
                        }

                        return (buttony / (2 * d)) + 4; // visszaadja a vásárolni kívánt termény sorszámát
                    }
            }
        }

        buttonx = clickevent.button.x;
        buttony = clickevent.button.y;

        if(buttonx > 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 && buttonx < 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 + 2*SCREEN_WIDTH / 50 && buttony > SCREEN_WIDTH / 10 + 11*SCREEN_WIDTH / 50 && buttony < SCREEN_WIDTH / 10 + 11*SCREEN_WIDTH / 50 + 2*SCREEN_WIDTH / 50)
        {
            reset();
        } else if(buttonx > 3*SCREEN_WIDTH / 4 + 6*SCREEN_WIDTH / 50 && buttonx > 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 + 2*SCREEN_WIDTH / 50 && buttony > SCREEN_WIDTH / 10 + 11*SCREEN_WIDTH / 50 && buttony < SCREEN_WIDTH / 10 + 11*SCREEN_WIDTH / 50 + 2*SCREEN_WIDTH / 50)
        {
            if(player == true)
            {
                printf("%d", 1);
                scanPlayer2();
                sendPlayer2();
                player = false;
            }
            else
            {
                printf("%d", 0);
                scan();
                send();
                player = true;
            }
        }

        else if(buttonx > 3*SCREEN_WIDTH / 4 + 3*SCREEN_WIDTH / 50 && buttonx < SCREEN_WIDTH - 2*SCREEN_WIDTH / 50 && buttony > SCREEN_WIDTH / 10 + 9*SCREEN_WIDTH / 50 && buttony < SCREEN_WIDTH / 10 + 9*SCREEN_WIDTH / 50 + BUTTON_HEIGHT)
        {
            return 13; // ez azt jelenti, hogy a játékos aratni szeretne
        }
    }
    return -1;
}

void planting()
{
    int i = buttonEventHandler();
    if(i == -1)
    {
        return; // ha se nem vesz, elad vagy arat a játékos
    }

    // az eladás már kezelve van közvetlenül a buttonEventHandler() függvényben

    if( i >= 0 && i < 4 ) // ha vesz
    {
        if(money - buy_price[i-1] < 0)
        {
            return;
        }

        int sorszam = goods();

        printf("---\ni: %d sorszam: %d\n---\n", i, sorszam);

        int x;
        int y;
        int d = (int)(agyas*SCREEN_WIDTH);

        if(sorszam <= 3)
        {
            x = 2*SCREEN_WIDTH / 50;
            y = 7*SCREEN_WIDTH / 50 + (sorszam - 1)*d;

        } else
        {
            x = 2*SCREEN_WIDTH / 50 + d;
            y = 7*SCREEN_WIDTH / 50 + (sorszam - 4)*d;
        }

        if(hely[sorszam-1].size == 0)
        {
            hely[sorszam-1].type = i;
            hely[sorszam-1].size = 1;
            money -= buy_price[i-1];
        }

        printf("%d %d\n", x, y); // a két koordinátája annak a pontnak, ahova ültetni kell a növényeket
    }
    else if( i == 13 )
    {
        int sorszam = goods();
        if(hely[sorszam-1].size == 3)
        {
            money += sell_price[hely[sorszam-1].type-1];
            hely[sorszam-1].size = 0;
            hely[sorszam-1].type = 0;
        }
    }

}