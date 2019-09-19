#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "map.h"
#include "objects.h"
#include "player.h"
#include "textures.h"
#include "../menu/menu.h"
#include "../network/network.h"

#define SPEED 1
#define SCREENSIZEX 1216
#define SCREENSIZEY 960
#define TEXTURESSIZE 10
#define CASE_SIZE 64
#define BOMB_POWER 1

enum enDirection
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef struct stGame
{
  SDL_Point screenSize;
  SDL_Window *pWindow;
  SDL_Renderer *pRenderer;

  stPlayer players[4];
  stObject *object;
  stMap *map;
  stTexture *texture[TEXTURESSIZE];

  unsigned int lastTime, presentTime, delta;
} stGame;

stGame *game_init();
void sdl_load(stGame *game, char *paths[], int arrayLength);
void player1_init(stGame *game);
void player2_init(stGame *game);
void map_init(stGame *game);
void object_init(stGame *game);
void textures_init(stGame *game);
void draw_map(stGame *game);
void character_sort(int nPlayer, stPlayer *player);

void draw_bomb(stGame *game);
void create_bomb(stGame *game, stPlayer *player);
void add_NewBomb(stGame *game, bomb *newBomb);
void destroy_bomb(stGame *game, bomb *endBomb);
int position_bomb(stGame *game, bomb *newBomb, stPlayer *player);

void draw_explosion(stGame *game);
void create_explosion(stGame *game, bomb *bomb);
void add_newExplosion(stGame *game, explosion *newExplosion);
void destroy_explosion(stGame *game, explosion *endexplosion);
int position_explosion(bomb *bomb, explosion *newExplosion);
void create_children_explosion(stGame *game, bomb *bomb);
int create_child_explosion(stGame *game, int tileX, int tileY,
                           unsigned int timer);
void player_flame_colision(stGame *game, stPlayer *player);

int game_event(stGame *game);
void game_destroy(stGame *game);
void game_boucle(stGame *game);

void game_draw(stGame *game);
void character_move(enum enDirection direction, stGame *game, stPlayer *player);

int check_collision(stGame *game, int x, int y);

void textures_destroy(stGame *game);

stGame *game_network_init(SDL_Window *pWindow, SDL_Renderer *pRenderer);
void game_network_event(int *step, stGame *game);

int client_event_read_network(int server, stGame *game);
void character_move_in_network(int event, stGame *game);
int create_track_client(int *my_socket, int clients_array[], stGame *game);

#endif