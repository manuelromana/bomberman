#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define PATHFGRAFITI "assets/font/Grafiti.ttf"
#define PATHFNEON "assets/font/Neon.ttf"

#define TXTSURFHOSTNAME "Tapez l'hostname suivi d'entree :"
#define TXTSURFPORTNAME "Tapez le numero de port puis entree : "
#define FONTCOLOR {0,0,0}


#define LEN(arr)  ( (int) (sizeof(arr)/sizeof(arr[0])) )

typedef struct stFont {
    SDL_Surface *surface;
    SDL_Texture *texture;
} stFont;

#endif