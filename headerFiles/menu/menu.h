#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../network/network.h"
#include "fonts.h"
#include "../game/game.h"
#include "../game/textures.h"

#define MENUDISPLAYX 10
#define MENUDISPLAYY 60
#define MENUDISPLAYW 600
#define MENUDISPLAYH 100
#define TEXTURESMENUSIZE 1

#define INPUTPOSITIONX 60
#define INPUTPOSITIONY 160
#define INPUTPOSITIONW(width) (15 * width)
#define INPUTPOSITIONH 50
#define PATHMENU "../../assets/bomberman.png"

typedef struct stMenu
{
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    TTF_Font *police1;
    TTF_Font *police2;
    TTF_Font *police3;

    //vaiables utilisées pour load les ttf
    SDL_Surface *surface;
    SDL_Texture *texture;

    SDL_Surface *surfaceMenu;
    SDL_Texture *textureMenu;
    SDL_Texture *pTextHostname;
    SDL_Texture *pTextPortname;
    SDL_Texture *pTextWelcome;
    SDL_Texture *pTextChoix;
    SDL_Texture *pInputText;
    SDL_Texture *pTextheberger;
    SDL_Texture *pTextRejoindre;

    SDL_Rect inputPositionRect;
    SDL_Rect hostamePositionRect;
    SDL_Rect portPositionRect;
    SDL_Rect welcomePositionRect;
    SDL_Rect choixPositionRect;
    SDL_Rect hebergerPostionRect;
    SDL_Rect rejoindrePostionRect;

} stMenu;

stMenu *menu_init(SDL_Window *pWindow, SDL_Renderer *pRenderer);
SDL_Texture *font_load(stMenu *menu, TTF_Font *police, char *content);
SDL_Texture *font_load_shaded(stMenu *menu, TTF_Font *police, char *content);
void menu_draw(stMenu *menu);
void menu_draw_choix(stMenu *menu, char *choix);
void menu_draw_hostname(stMenu *menu, char *hostname);
void menu_draw_port(stMenu *menu, char *port);
void menu_draw_welcome(stMenu *menu);

void menu_event(SDL_Event event, int *step, char **currentText, char *hostname, char *port, int socket_target);

void menu_destroy_2(stMenu *menu);
#endif