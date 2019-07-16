#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>

typedef struct
{
    //Fenêtre
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    SDL_Surface *text;

    //Textures
    SDL_Texture *pTexPlayer;
    SDL_Texture *pTexBomb;
    SDL_Texture *pTexText;

    SDL_Rect playerPositionRect;
    SDL_Rect bombPositionRect;
    SDL_Rect textPositionRect;
} stGame;

stGame *game_init_2();
void game_destroy_2(stGame *game);
int game_event_2();
void game_draw_2(stGame *game);

int my_strlen(char *str);
int read_client(int client);
int read_server(int server);

void game_draw(stGame *game, int flagBomb);
void character_move(SDL_Keycode direction, stGame *game);
void Redraw();

#endif