#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define HAUTEURMAP 15
#define LARGEURMAP 19

typedef struct {
    int playerDirection;

    SDL_Rect playerPositionRect;
} playerPosition;

typedef struct {
    SDL_Texture* pTexPlayerFront;
    SDL_Texture* pTexPlayerBack;
    SDL_Texture* pTexPlayerRight;
    SDL_Texture* pTexPlayerLeft;

    playerPosition* pPos1;
} player;

typedef struct {
    int map[HAUTEURMAP][LARGEURMAP];
    
    SDL_Texture* pTexBomb;
    SDL_Texture* pTexWall;
    SDL_Rect bombPositionRect;
    SDL_Rect wallPosition;
} stMap;

typedef struct {
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    playerPosition* pPos1;
    player* p1;
    stMap* map;
} stGame;

playerPosition* playerPosition_init(stGame* game, player* p1);
player* player_init(stGame* game);
stMap* map_init(stGame* game);
stGame* game_init();

int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);

void game_destroy(stGame *game);
void player_destroy(player* p1);
void map_destroy(stMap* map);

void draw_bomb(stGame* game);
void game_draw(stGame* game);
void draw_map(stGame* game);
void load_map(stGame* game);

void load_surface(SDL_Surface* surface, stGame *game);

#endif