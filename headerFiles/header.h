#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define HAUTEURMAP 15
#define LARGEURMAP 19
#define SCREENSIZEX 1216
#define SCREENSIZEY 960
#define BOMBPOSITION 1300
#define PLPOSITIONX ( SCREENSIZEX / 2 )
#define PLPOSITIONY ( SCREENSIZEY / 2 )
#define WALLPOSITIONW 64
#define WALLPOSITIONH 128
#define PLAYERPOSITIONRECTW 64
#define PLAYERPOSITIONRECTH 128

#define LIMITX ( SCREENSIZEX - PLAYERPOSITIONRECTW )
#define LIMITY ( SCREENSIZEY - PLAYERPOSITIONRECTH )

typedef struct {
    SDL_Point screenSize;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;

    SDL_Texture* pTexPlayerFront;
    SDL_Texture* pTexPlayerBack;
    SDL_Texture* pTexPlayerRight;
    SDL_Texture* pTexPlayerLeft;
    SDL_Texture* pTexBomb;
    SDL_Texture* pTexWall;

    int playerDirection;

    SDL_Rect playerPositionRect;
    SDL_Rect bombPositionRect;
    SDL_Rect wallPosition;

    int map[HAUTEURMAP][LARGEURMAP];
} stGame;


stGame* game_init();

int game_event(stGame *game);
void character_move(SDL_Keycode direction, stGame *game);
void game_destroy(stGame* game);
void draw_bomb(stGame* game, int flagBomb);
void game_draw(stGame* game);
void draw_map(stGame* game);
void load_map(stGame* game);

#endif