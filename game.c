//
// Created by Tomi on 26/10/2018.
//

#include <string.h>
#include "game.h"
#include "global.h"
#include "textures.h"
#include "elements.h"
#include "fields.h"

ElementType currentAction = et_RESET;

int init() {

    bool success = true;

    // Initializing everything, setting up the playground
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // creating the window
    SDL_Window *window = SDL_CreateWindow("FarmVik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }
    // creating the renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == NULL) {
        printf("Error: %s\n", SDL_GetError());
        success = false;
        return success;
    }

    // setting up background color

    SDL_SetRenderDrawColor(renderer, 76, 175, 80, SDL_ALPHA_OPAQUE);

    return success;
}

void scan(Players players) {
    FILE *data = NULL;

    if (players == ONE)
        data = fopen("gameData.txt", "r");
    else if (players == TWO)
        data = fopen("gameDataPlayer2.txt", "r");

    if (data != NULL) {

        fscanf(data, "%d %d %d %d", &money, &apple, &potato, &tomato);

        int column, row;
        fscanf(data, "%d %d\n", &column, &row);
        setupFields(column, row);

        for (int i = 0; i < columns; i++)
            for (int j = 0; j < rows; j++)
                fscanf(data, "%d %d %d %d\n", &fields[i][j].timePlanted, &fields[i][j].age, &fields[i][j].type,
                       &fields[i][j].index);

        fclose(data);
    } else {
        printf("Error: Could not open the file");
    }
}

void save(Players players) {
    FILE *data = NULL;

    if (players == ONE)
        data = fopen("gameData.txt", "w");
    else if (players == TWO)
        data = fopen("gameDataPlayer2.txt", "w");

    if (data != NULL) {

        fprintf(data, "%d %d %d %d\n", money, apple, potato, tomato);

        fprintf(data, "%d %d\n", columns, rows);

        for (int i = 0; i < columns; i++)
            for (int j = 0; j < rows; j++)
                fprintf(data, "%d %d %d %d\n", fields[i][j].timePlanted, fields[i][j].age, fields[i][j].type,
                        fields[i][j].index);

        fclose(data);
    } else {
        printf("Error: Could not open the file");
    }
}

void reset() {
    freeFields();
    setupFields(1, 3);

    money = 1000;
    apple = potato = tomato = 0;
}

void handleButtons(Players *player) {
    for (int i = 0; i < 3; i++) {
        if (isOverElement(buy[i])) { // megadja a függvény, hogy az adott ikon felett van-e az egerünk a kattintáskor
            currentAction = et_BUY1 + i; // az ElementType típusú currentActiont az i-edik vásárlás gombra változtatja
        } else if (isOverElement(sell[i])) { // melyik eladás gombon van az egér
            switch (sell[i].e_type) {
                case et_SELL1:
                    if (apple > 0) {
                        money += apple * sell_price[sell[i].e_type - et_SELL1];
                        apple = 0;
                    }
                    break;
                case et_SELL2:
                    if (potato > 0) {
                        money += potato * sell_price[sell[i].e_type - et_SELL1];
                        potato = 0;
                    }
                    break;
                case et_SELL3:
                    if (tomato > 0) {
                        money += tomato * sell_price[sell[i].e_type - et_SELL1];
                        tomato = 0;
                    }
                    break;
                default:
                    printf("Error in isOver sell!");
                    break;
            }
        }
    }
    if (isOverElement(resetButton)) {
        currentAction = et_RESET;
        reset();
    } else if (isOverElement(change)) {
        currentAction = et_CHANGE;
        save(*player);
        freeFields();
        if (*player == TWO) *player = ONE;
        else *player = TWO;
        scan(*player);
    } else if (isOverElement(harvest)) {
        currentAction = et_HARVEST;
    } else if (isOverElement(destroy)) {
        currentAction = et_DESTROY;
    } else if (isOverElement(move)) {
        currentAction = et_MOVE;
        if (columns < 4 && money >= 10000) {
            addColumn();
            money -= 10000;
        }
    }
}

void handleFields() {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            if (isOverField(fields[i][j])) { // megnézi, hogy melyik mezőn van az egér
                switch (currentAction) {
                    case et_BUY1:
                    case et_BUY2:
                    case et_BUY3:
                        if (money >= buy_price[buy[i].e_type]) { // az adott számú mezőnél attól függően hogy mit akarunk vásárolni, levonja a termény árát a buy_price tömbből
                            money -= buy_price[buy[i].e_type];
                            bed(&fields[i][j],(PlantType) currentAction); // majd el is ülteti az adott terményt
                            // nem változtat semmit az értékén, csak PlantType típusú enumot vár a függvény, ezért átkonvertálom (különben szól a fordító)
                        }
                        break;
                    case et_HARVEST: // itt kezelem az aratás folyamatát
                        if (fields[i][j].age != a_DEAD) { // ha éppen van a mezőn növésben lévő/kifejledt termény
                            if (fields[i][j].age == a_BIG) { // és már ki is nőtt teljesen
                                switch (fields[i][j].type) { // akkor megnézi a típusát
                                    // majd növeli a termény mennyiségét
                                    case pt_APPLE:
                                        apple += 5;
                                        break;
                                    case pt_POTATO:
                                        potato += 5;
                                        break;
                                    case pt_TOMATO:
                                        tomato += 5;
                                        break;
                                    default:
                                        /*semmmi*/
                                        break;
                                }
                            }
                            resetFieldData(&fields[i][j]); // az adott mező minden értékét alapértékre állítja
                        }
                        break;
                    case et_DESTROY: // a kiásást kezeli
                        if (fields[i][j].age == a_DEAD && money >= 500) { // ha van 500 aranya a játékosnak, és halott az adott mezőn lévő termény
                            resetFieldData(&fields[i][j]); // akkor reseteli a mezőt
                            money -= 500; // és levon 500 aranyat
                        }
                        break;
                    default:
                        /*semmi*/
                        break;
                }
            }
        }
    }
}

void eventHandler(SDL_Event event, Players *player) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {

            if (event.button.x != -1 && event.button.y != -1) {
                mouseX = event.button.x;
                mouseY = event.button.y;
            }

            handleButtons(player);
            handleFields();
        }
    }
}