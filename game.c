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

void handleButtons()
{
    for(int i=0; i<3;i++) {
        if( isOverElement(buy[i])) {
            if(money >= buy_price[buy[i].e_type]) {
                currentAction = BUY1 + i;
                currentPlant  = t_APPLE + i;
                money -= buy_price[buy[i].e_type];
            }
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
        if(money >= 5000) {
            currentAction = et_DESTROY;
            money -= 5000;
        }
    }
}

void handleFields()
{
    for(int i=0;i<rows;i++) {
        for(int j=0;j<columns;j++){
            switch(currentAction) {
                case BUY1:
                case BUY2:
                case BUY3:
                    if(isOverField(fields[i][j]))
                        bed(&fields[i][j],currentPlant);
                    break;
                case et_HARVEST:
                    break;
                case et_DESTROY:
                    break;
                default:
                    /*semmi*/
                    break;
            }
        }
    }
}

void eventHandler()
{
    SDL_WaitEvent(&clickevent);
    if(clickevent.type == SDL_MOUSEBUTTONDOWN) {
        if (clickevent.button.button == SDL_BUTTON_LEFT) {

            if(clickevent.button.x != -1 && clickevent.button.y != -1) {
                mouseX = clickevent.button.x;
                mouseY = clickevent.button.y;
            }

            handleButtons();
            handleFields();
        }
    }
}