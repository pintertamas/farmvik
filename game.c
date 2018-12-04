//
// Created by Tomi on 26/10/2018.
//

#include <string.h>
#include "game.h"
#include "global.h"
#include "textures.h"
#include "elements.h"
#include "fields.h"

ElementType currentAction = false;
PlantType   currentPlant  = t_APPLE;

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
    SDL_Window *window = SDL_CreateWindow( "FarmVik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

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
        fscanf(data, "%d %d\n", &hely[i].type, &hely[i].size);
    for(int i=0;i<6;i++)
        fscanf(data, "%d ", &times[i]);
    fscanf(data, "\n%d\n%d %d %d", &money, &apple, &potato, &tomato);

    if (data != NULL)
        fclose(data);
    else
        printf("Error: Could not open the file");
}

int plantnumber()
{
    bool click = false;
    int n = (int)(agyas*SCREEN_WIDTH);
    int buttonx = -1;
    int buttony = -1;
    SDL_WaitEvent(&clickevent);

    switch(clickevent.type) {
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
            if (clickevent.button.button == SDL_BUTTON_LEFT)
                click = false;
            break;
        default:
            break;
    }

    if(click == true) {
        if( buttonx > 0 && buttonx < n && buttony > 0 && buttony < 3 * n )
            return (buttony / n) + 1;
        else if( buttonx > n && buttonx < 2 * n && buttony > 0 && buttony < 3 * n )
            return (buttony / n) + 4;
    }
    plantnumber();
}

int buttonEventHandler()
{
    SDL_WaitEvent(&clickevent);
    if(clickevent.type == SDL_MOUSEBUTTONDOWN) {
        if (clickevent.button.button == SDL_BUTTON_LEFT) {

            if(clickevent.button.x != -1 && clickevent.button.y != -1) {
                mouseX = clickevent.button.x;
                mouseY = clickevent.button.y;
            }

            for(int i=0; i<3;i++) {
                if( isOverElement(buy[i])) {
                    currentAction = BUY1 + i;
                    currentPlant  = t_APPLE + i;
                } else if( isOverElement(sell[i])) {
                    switch(sell[i].e_type) {
                        case SELL1:
                            if(apple > 0) {
                                money += apple * sell_price[sell[i].e_type - SELL1];
                                apple = 0;
                            }
                            break;
                        case SELL2:
                            if(potato > 0) {
                                money += potato * sell_price[sell[i].e_type - SELL1];
                                potato = 0;
                            }
                            break;
                        case SELL3:
                            if(tomato > 0) {
                                money += tomato * sell_price[sell[i].e_type - SELL1];
                                tomato = 0;
                            }
                            break;
                        default:
                            printf("Error in isOver sell!");
                            break;
                    }
                }
            }
            if(isOverElement(resetButton)) {
                currentAction = et_RESET;
                reset();
            } else if(isOverElement(change)) {
                currentAction = et_CHANGE;
                if(player == true) {
                    scan(TWO);
                    send(TWO);
                    player = false;
                } else {
                    scan(ONE);
                    send(ONE);
                    player = true;
                }
            } else if(isOverElement(harvest)) {
                currentAction = et_HARVEST;
            } else if(isOverElement(destroy)) {
                currentAction = et_DESTROY;
            }
        }
    }
}

void planting()
{
    int i = buttonEventHandler();
    if(i == -1)
        return; // ha se nem vesz, elad vagy arat a játékos

    // az eladás már kezelve van közvetlenül a buttonEventHandler() függvényben

    if( i >= 0 && i < 4 ) // ha vesz
    {
        if( money - buy_price[i - 1] < 0 )
            return;

        int sorszam = plantnumber();

        if( hely[sorszam - 1].size == 0 ) {
            hely[sorszam - 1].type = i;
            hely[sorszam - 1].size = 1;
            money -= buy_price[i - 1];
            times[sorszam - 1] = time(0);
        }

    } else if( i == 13 ) {
        int sorszam = plantnumber();
        if( hely[sorszam - 1].size == 3 ) {
            //money += sell_price[hely[sorszam-1].type-1];

            switch( hely[sorszam - 1].type ) {
                case 1:
                    apple += hely[sorszam - 1].type;
                    break;
                case 2:
                    potato += hely[sorszam - 1].type;
                    break;
                case 3:
                    tomato += hely[sorszam - 1].type;
                    break;
                default:
                    break;
            }

            hely[sorszam - 1].size = 0;
            hely[sorszam - 1].type = 0;
            times[sorszam - 1] = 0;
        }
    } else if( i == 14) {
        if(money < 5000)
            return;
        money -= 5000;
        int sorszam = plantnumber();
        hely[sorszam-1].size = 0;
        hely[sorszam-1].type = 0;
        times[sorszam-1] = 0;
    }
}