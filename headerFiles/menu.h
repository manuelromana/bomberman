#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include "network.h"
#include "fonts.h"
#include "game/game.h"

#define SCREENSIZEX 640
#define SCREENSIZEY 480

#define MENUDISPLAYX 10
#define MENUDISPLAYY 60
#define MENUDISPLAYW 600
#define MENUDISPLAYH 100

#define INPUTPOSITIONX 60
#define INPUTPOSITIONY 160
#define INPUTPOSITIONW(width) (15 * width)
#define INPUTPOSITIONH 50

typedef struct stMenu
{
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    TTF_Font *police1;
    TTF_Font *police2;

    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Texture *pTextHostname;
    SDL_Texture *pTextPortname;
    SDL_Texture *pTextWelcome;
    SDL_Texture *pTextChoix;
    SDL_Texture *pInputText;

    SDL_Rect inputPositionRect;
    SDL_Rect hostamePositionRect;
    SDL_Rect portPositionRect;
    SDL_Rect welcomePositionRect;
    SDL_Rect choixPositionRect;
} stMenu;

stMenu *menu_init_2();
SDL_Texture *font_load(stMenu *menu, TTF_Font *police, char *content);

void menu_draw_choix(stMenu *menu, char *choix);
void menu_draw_hostname(stMenu *menu, char *hostname);
void menu_draw_port(stMenu *menu, char *port);
void menu_draw_welcome(stMenu *menu);

void menu_destroy_2(stMenu *menu);
#endif