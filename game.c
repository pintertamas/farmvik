//
// Created by Tomi on 26/10/2018.
//

#include <string.h>
#include "game.h"
#include "global.h"
#include "textures.h"
#include "elements.h"

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

void scan(Players players)
{
    FILE* data = NULL;

    if(players == ONE) {
        data = fopen("gameData.txt", "r");
    } else if(players == TWO) {
        data = fopen("gameDataPlayer2.txt", "r");
    }

    if (data != NULL) {
        for(int i=0;i<6;i++)
            fscanf(data, "%d %d\n", &hely[i].type, &hely[i].size);

        for(int i=0;i<6;i++)
            fscanf(data, "%d ", &times[i]);

        fscanf(data, "%d\n%d %d %d", &money, &apple, &potato, &tomato);
        fclose(data);
    } else {
        printf("Error: Could not open the file");
    }
}

void send(Players players)
{
    FILE* data = NULL;

    if(players == ONE)
        data = fopen("gameData.txt", "w");
    else if(players == TWO)
        data = fopen("gameDataPlayer2.txt", "w");

    if(data != NULL) {
        for(int i=0;i<6;i++)
            fprintf(data, "%d %d\n", hely[i].type, hely[i].size);
        for(int i=0;i<6;i++)
            fprintf(data, "%d ",  times[i]);
        fprintf(data, "\n%d\n%d %d %d", money, apple, potato, tomato);
        fclose(data);
    } else {
        printf("Error: Could not open the file");
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
    for(int i=0;i<6;i++)
    {
        fscanf(data, "%d ",  &times[i]);
    }
    fscanf(data, "\n%d\n%d %d %d", &money, &apple, &potato, &tomato);

    if (data != NULL)
    {
        fclose(data);
    } else{
        printf("Error: Could not open the file");
    }
}

int plantnumber()
{
    bool click = false;
    int n = (int)(agyas*SCREEN_WIDTH);
    int buttonx = -1;
    int buttony = -1;
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
        if(buttonx > 0 && buttonx < n && buttony > 0 && buttony < 3*n)
        {
            return (buttony / n) + 1;
        }
        else if(buttonx > n && buttonx < 2*n && buttony > 0 && buttony < 3*n)
        {
            return (buttony / n) + 4;
        }
    }
    plantnumber();
}

int buttonEventHandler()
{
    int BUTTON_HEIGHT = d; // a gombok mérete, létrehozáskor buttonw és buttonh volt a nevük, csak név ütközés miatt most máshogy nevezem el.
    int BUTTON_WIDTH = (int)round((double)SCREEN_WIDTH / 20);
    bool click = false;
    int buttonx = -1;
    int buttony = -1;
    SDL_WaitEvent(&clickevent);

    switch(clickevent.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (clickevent.button.button == SDL_BUTTON_LEFT) {
                click = true;

                if(clickevent.button.x != -1 && clickevent.button.y != -1)
                {
                    buttonx = clickevent.button.x;
                    buttony = clickevent.button.y;
                    setMousePos(clickevent.button.x, clickevent.button.y);
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
        for(int i=0; i<3;i++)
        {
            if (isOver(buy[i]))
            {
                printf("zzz");
                return (buttony / (2 * d)) + 1; // visszaadja a vásárolni kívánt termény sorszámát
            }
            else if (isOver(sell[i]))
            {
                printf("zzz");

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
        if(isOver(resetButton))
        {
            reset();
        }
        else if(isOver(change))
        {
            if(player == true)
            {
                scan(TWO);
                send(TWO);
                player = false;
            }
            else
            {
                scan(ONE);
                send(ONE);
                player = true;
            }
        }

        else if(isOver(harvest))
        {
            //return 13;
        }
        else if(isOver(destroy))
        {
            //return 14;
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

        int sorszam = plantnumber();

        if(hely[sorszam-1].size == 0)
        {
            hely[sorszam-1].type = i;
            hely[sorszam-1].size = 1;
            money -= buy_price[i-1];
            times[sorszam-1] = time(0);
        }

    }
    else if( i == 13 )
    {
        int sorszam = plantnumber();
        if(hely[sorszam-1].size == 3)
        {
            //money += sell_price[hely[sorszam-1].type-1];

            switch(hely[sorszam-1].type)
            {
                case 1:
                    apple += hely[sorszam-1].type;
                    break;
                case 2:
                    potato += hely[sorszam-1].type;
                    break;
                case 3:
                    tomato += hely[sorszam-1].type;
                    break;
                default:
                    break;
            }

            hely[sorszam-1].size = 0;
            hely[sorszam-1].type = 0;
            times[sorszam-1] = 0;
        }
    }
    else if( i == 14)
    {
        if(money < 5000)
        {
            return;
        }
        money -= 5000;
        int sorszam = plantnumber();
        hely[sorszam-1].size = 0;
        hely[sorszam-1].type = 0;
        times[sorszam-1] = 0;
    }
}

void timePassed()
{
    for(int i=0;i<6;i++)
    {
        if(times[i] != 0)
        {
            if(time(0) - times[i] == 4 && hely[i].size == 1)
            {
                hely[i].size++;
            }
            else if(time(0) - times[i] == 8 && hely[i].size == 2)
            {
                hely[i].size++;
            }
            else if(time(0) - times[i] >= 25 && hely[i].size == 3)
            {
                hely[i].size = 4;
            }
        }
    }
}