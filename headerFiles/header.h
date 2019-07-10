#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>

typedef struct
{
    //Fenêtre
    SDL_Point screenSize;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

    //Textures
    SDL_Texture *pTexPlayer;
    SDL_Texture *pTexBomb;

    SDL_Rect playerPositionRect;
    SDL_Rect bombPositionRect;
} stGame;

stGame *game_init();
void game_destroy(stGame *game);
void game_draw(stGame *game, int flagBomb);
int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);
int my_strlen(char *str);
int read_client(int client);

#endif