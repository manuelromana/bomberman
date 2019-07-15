#include "../headerFiles/header.h"

int game_event_2(stGame *game)
{
    int quit = 0;
    SDL_Event event;
    char *text;
    text = malloc(sizeof(char *) * 10);
    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        if ()
        {
        }
        else if (event.type == SDL_QUIT)
        {
            quit = -1;
        }
    }

    return quit;
}