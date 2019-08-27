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
#include "../headerFiles/network.h"

#define SCREENSIZEX 640
#define SCREENSIZEY 480

#define MENUDISPLAYX 10
#define MENUDISPLAYY 60
#define MENUDISPLAYW 600
#define MENUDISPLAYH 100

#define INPUTPOSITIONX 60
#define INPUTPOSITIONY 160
#define INPUTPOSITIONW(width) ( 15 * width )
#define INPUTPOSITIONH 50


#include "fonts.h"
typedef struct
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rectangle;
    char *path;
} st_img;

typedef struct
{
    //Fenêtre
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
    st_img *images[10];
} st_game;

typedef struct
{
    //Fenêtre
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    TTF_Font *police1;
    TTF_Font *police2;

    SDL_Surface *surface;
    SDL_Texture *texture;

    //Textures
    SDL_Texture *pTexPlayer;
    SDL_Texture *pTexBomb;
    SDL_Texture *pTextHostname;
    SDL_Texture *pTextPortname;
    SDL_Texture *pTextWelcome;
    SDL_Texture *pTextChoix;

    SDL_Texture *pInputText;

    SDL_Rect inputPositionRect;

    SDL_Rect playerPositionRect;
    SDL_Rect bombPositionRect;
    SDL_Rect hostamePositionRect;
    SDL_Rect portPositionRect;
    SDL_Rect welcomePositionRect;
    SDL_Rect choixPositionRect;
} stGame;

stGame *game_init_2();

void game_destroy_2(stGame *game);
int game_event_hostname(char *hostname);
int game_event_port(char *hostname);
void game_draw_choix(stGame *game, char *choix);
void game_draw_hostname(stGame *game, char *hostname);
void game_draw_port(stGame *game, char *port);
void send_key(SDL_Keycode keydown, int mysocket);
void game_draw_welcome(stGame *game);
void control_event(SDL_Event event, int *step, char **currentText, char *hostname, char *port, int mysocket);
void track_client(int *server_socket);

void character_move(SDL_Keycode direction, stGame *game);
void Redraw();

st_game *game_init_test();
void game_destroy(st_game *game);
void draw_game_test(st_game *game);

SDL_Texture *font_load(stGame *game, TTF_Font *police, char *content);
#endif