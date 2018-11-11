//
// Created by Tomi on 26/10/2018.
//

#include <string.h>
#include "game.h"
#include "global.h"
#include "textures.h"

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

    if( NULL == window )
    {
        printf( "Error: %s\n", SDL_GetError() );
        success = false;
        return success;
    }
    // creating the renderer
    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( NULL == renderer )
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
    fscanf(data, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &a, &am, &b, &bm, &c, &cm, &d, &dm, &e, &em, &f, &fm, &money, &apple, &potato, &tomato);
    // a,b,c,d,e,f: egyes cellák típusai (pl alma)
    // am, bm, ... fm: azt jelzik, hogy az ott lévő termények mekkorák
    am = places[0][0];
    bm = places[0][1];
    cm = places[0][2];
    dm = places[1][0];
    em = places[1][1];
    fm = places[1][2];
    fclose(data);
}

void send()
{
    FILE* data;
    data = fopen("gameData.txt", "w");
    fprintf(data, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            am, places[0][0], bm, places[0][1], cm, places[0][2],
            dm, places[1][0], em, places[1][1], fm, places[1][2], money, apple, potato, tomato);
    fclose(data);
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
            places[0][buttony / d] = 1;
            return (buttony / d) + 1;
        }
        else if(buttonx > d && buttonx < 2*d && buttony > 0 && buttony < 3*d)
        {
            //printf("%d\n", (buttony / d) + 4);
            places[1][buttony / d] = 1;
            return (buttony / d) + 4;
        }
    }
    goods();
}

typedef enum Hasznalat{BUY,SELL}Hasznalat;

int buttonbuy(Hasznalat transaction)
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
                if(transaction == BUY) // tehát venni szeretnénk
                {
                    if (0 <= buttonx && buttonx <= BUTTON_WIDTH && (i * 2 * d) <= buttony && buttony <= d + (i * 2 * d))
                    {
                        //printf("%d\n", (buttony / (2 * d)) + 1);
                        return (buttony / (2 * d)) + 1;
                    }
                }

                else if(transaction == SELL) // vagy eladni
                {
                    if ((BUTTON_WIDTH + d) <= buttonx && buttonx <= (BUTTON_WIDTH + d) + BUTTON_WIDTH && (i * 2 * d) <= buttony && buttony <= d + (i * 2 * d))
                    {
                        //printf("%d\n", (buttony / (2 * d)) + 1);
                        return (buttony / (2 * d)) + 1;
                    }
                }
            }
        }
    }
    return -1;
}

void bed(int x, int y, int i)
{
    int d = (int)(agyas*SCREEN_WIDTH);
    SDL_Rect rect = { x, y, d, d };
    //printf("\n %d %d \n", x, y);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderCopy(renderer, textures[i], NULL, &rect);
}

void planting()
{
    int i = buttonbuy(BUY);
    if(i == -1)
    {
        return;
    }
    int sorszam = goods();
    money -= buy_price[i-1];

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

    printf("%d %d\n", x, y); // a két koordinátája annak a pontnak, ahova ültetni kell a növényeket

    bed(x, y, 10 + 3*(i-1));
}

void sell()
{
    int i = buttonbuy(SELL);
    if(i == -1)
    {
        return;
    }
    money += sell_price[i-1];

    printf("---\ni: %d\n---", i);


}