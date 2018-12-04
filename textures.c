//
// Created by Tomi on 27/10/2018.
//

#include "textures.h"
#include "global.h"
#include "game.h"

// initializing pictures
SDL_Texture *loadTexture(char *path)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *image = IMG_Load(path);

    if( NULL == image )
    {
        printf( "Error1: %s\n", SDL_GetError( ) );
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, image);

        if( NULL == texture )
        {
            printf( "Error2: %s\n", SDL_GetError( ) );
        }
        SDL_FreeSurface(image);
    }
    return texture;
}

SDL_Texture* getElementTexture(textureIndex index)
{
    return textures[index];
}

void loadImage() // ÚJABB KÉP FELTÖLTÉSE UTÁN A TÖMB MÉRETÉT IS NÖVELNI KELL A global.h-BAN ÉS A global.c-BEN IS!
{
    textures[0] = loadTexture("Textures/logo_300x300.png");
    textures[1] = loadTexture("Textures/logo_bal.png");
    textures[2] = loadTexture("Textures/logo_jobb.png");
    textures[3] = loadTexture("Textures/buy.png");
    textures[4] = loadTexture("Textures/sell.png");
    textures[5] = loadTexture("Textures/dirt.png");
    textures[6] = loadTexture("Textures/tombstone.png");
    textures[7] = loadTexture("Textures/harvest.png");
    textures[8] = loadTexture("Textures/reset.png");
    textures[9] = loadTexture("Textures/gpsw.png");
    textures[10] = loadTexture("Textures/destroy.png");

    textures[11] = loadTexture("Textures/coin.png");
    textures[12] = loadTexture("Textures/apple.png");
    textures[13] = loadTexture("Textures/potato.png");
    textures[14] = loadTexture("Textures/tomato.png");

    textures[15] = loadTexture("Textures/alma_mag.png");
    textures[16] = loadTexture("Textures/krumpli_mag.png");
    textures[17] = loadTexture("Textures/paradicsom_mag.png");

    textures[18] = loadTexture("Textures/alma_csira.png");
    textures[19] = loadTexture("Textures/krumpli_csira.png");
    textures[20] = loadTexture("Textures/paradicsom_csira.png"); // kellene valami rendes grafika ehhez is, mert ez így tré

    textures[21] = loadTexture("Textures/alma_nagy.png");
    textures[22] = loadTexture("Textures/krumpli_nagy.png");
    textures[23] = loadTexture("Textures/paradicsom_nagy.png");
}


void background()
{
    SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(renderer, bggreen.r, bggreen.g, bggreen.b, bggreen.a);
    SDL_RenderFillRect(renderer, &background);
}

void doRender() {
    int NUMBER_OF_IMAGES = 3; // ennyi féle terményt lehet gondozni / növelni

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // setting up the design
    int fejlec = (int) round((double) SCREEN_WIDTH / 10);

    // logo
    SDL_Rect logo = {SCREEN_WIDTH / 2 - SCREEN_WIDTH / 20, 0, fejlec, fejlec};
    SDL_RenderCopy(renderer, textures[0], NULL, &logo);

    SDL_Rect logobal = {SCREEN_WIDTH / 2 - 3 * SCREEN_WIDTH / 20, 0, fejlec, fejlec};
    SDL_RenderCopy(renderer, textures[1], NULL, &logobal);

    SDL_Rect logojobb = {SCREEN_WIDTH / 2 + SCREEN_WIDTH / 20, 0, fejlec, fejlec};
    SDL_RenderCopy(renderer, textures[2], NULL, &logojobb);

    // bal oldali kis ikonok és a pénz jobb oldalon
    for(int i=0;i<NUMBER_OF_IMAGES;i++)
    {
        SDL_Rect icon = { d, (i+1)*d , d, d };
        SDL_RenderCopy(renderer, icon_textures[i+1], NULL, &icon);
    }
    // jobb oldalon a pénz ikon
    SDL_Rect coin = { 3*SCREEN_WIDTH / 4, d , d, d };
    SDL_RenderCopy(renderer, icon_textures[0], NULL, &coin);

    // ikonok a boltban
    for(int i=0; i<NUMBER_OF_IMAGES; i++)
    {
        SDL_Rect shop = { 3*SCREEN_WIDTH / 4 + d, 2*(i+1)*d + fejlec , SCREEN_WIDTH / 30, SCREEN_WIDTH / 30 };
        SDL_RenderCopy(renderer, icon_textures[i+1], NULL, &shop);

        SDL_Rect shoprect = { 3*SCREEN_WIDTH / 4 + d, 2*(i+1)*d + fejlec , SCREEN_WIDTH / 30, SCREEN_WIDTH / 30 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &shoprect);
    }

    // a nagy negyzet az egesz cucc kozepen meg a jobb oldali
    SDL_Rect bigrect = { d, d + fejlec, 3*SCREEN_WIDTH / 4 - 2*d, SCREEN_HEIGHT - 2*d - fejlec };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &bigrect);

    SDL_Rect smallrect = { 3*SCREEN_WIDTH / 4, fejlec + d, SCREEN_WIDTH / 4 - d, SCREEN_HEIGHT - fejlec - 2*d };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &smallrect);
}

int digit(int num)
{
    int counter = 0;
    while(num != 0)
    {
        num /= 10;
        ++counter;
    }
    if(counter == 0) return 1;
    return counter;
}

void score()
{
    TTF_CloseFont(font);
    font = TTF_OpenFont("Prototype.ttf", 25);

    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    int charwidth = (int)round((double)SCREEN_WIDTH / 100);

    SDL_Color black = { 255, 255, 255 };
    char moneybuffer[50];
    char applebuffer[50];
    char potatobuffer[50];
    char tomatobuffer[50];

    sprintf(moneybuffer, "%d gold", money);
    sprintf(applebuffer, "%d", apple);
    sprintf(potatobuffer, "%d", potato);
    sprintf(tomatobuffer, "%d", tomato);

    SDL_Texture *moneytxt;
    balance = TTF_RenderText_Solid(font, moneybuffer, black);
    moneytxt = SDL_CreateTextureFromSurface(renderer, balance);
    SDL_Rect moneybox = { 3*SCREEN_WIDTH / 4 + 2*d, d , digit(money)*charwidth + 5*charwidth, d };
    SDL_RenderCopy(renderer, moneytxt, NULL, &moneybox);
    SDL_FreeSurface(balance);

    SDL_Texture *appletxt;
    balance = TTF_RenderText_Solid(font, applebuffer, black);
    appletxt = SDL_CreateTextureFromSurface(renderer, balance);
    SDL_Rect applebox = { 2*d, d , digit(apple)*charwidth, d };
    SDL_RenderCopy(renderer, appletxt, NULL, &applebox);
    SDL_FreeSurface(balance);

    SDL_Texture *potatotxt;
    balance = TTF_RenderText_Solid(font, potatobuffer, black);
    potatotxt = SDL_CreateTextureFromSurface(renderer, balance);
    SDL_Rect potatobox = { 2*d, 2*d , digit(potato)*charwidth, d };
    SDL_RenderCopy(renderer, potatotxt, NULL, &potatobox);
    SDL_FreeSurface(balance);

    SDL_Texture *tomatotxt;
    balance = TTF_RenderText_Solid(font, tomatobuffer, black);
    tomatotxt = SDL_CreateTextureFromSurface(renderer, balance);
    SDL_Rect tomatobox = { 2*d, 3*d , digit(tomato)*charwidth, d };
    SDL_RenderCopy(renderer, tomatotxt, NULL, &tomatobox);
    SDL_FreeSurface(balance);
}

void bed(int x, int y, int i, int t)
{
    int n = (int)(agyas*SCREEN_WIDTH);
    SDL_Rect rect = { x, y, n, n };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    switch(t)
    {
        case 0:
            SDL_RenderCopy(renderer, textures[DIRT], NULL, &rect);
            break;
        case 1:
            SDL_RenderCopy(renderer, textures[M_ALMA + i], NULL, &rect);
            break;
        case 2:
            SDL_RenderCopy(renderer, textures[CS_ALMA + i], NULL, &rect);
            break;
        case 3:
            SDL_RenderCopy(renderer, textures[N_ALMA + i], NULL, &rect);
            break;
        case 4:
            SDL_RenderCopy(renderer, textures[TOMBSTONE], NULL, &rect);
            break;
        default:
            SDL_RenderCopy(renderer, textures[TOMBSTONE], NULL, &rect);
            break;
    }
}

void renderState()
{
    int n = (int)(agyas*SCREEN_WIDTH);

    for(int i=0;i<6;i++)
    {
        if(i < 3)
        {
            int x;
            int y;
            x = 2 * d;
            y = 7 * d + i * n;
            bed(x, y, hely[i].type - 1, hely[i].size);
        } else
        {
            int x = 2*d + n;
            int y = 7*d + (i - 3)*n;
            bed(x, y, hely[i].type - 1, hely[i].size);
        }
    }
}