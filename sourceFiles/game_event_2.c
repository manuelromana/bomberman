#include "../headerFiles/header.h"

int game_event_2()
{
    int quit = 0;
    SDL_Event event;
    char test[10];

    while (SDL_PollEvent(&event) != 0)
    {
        //User requests quit
        switch (event.type)
        {
        case (SDL_QUIT):
            quit = -1;
        case (SDL_TEXTINPUT):
            strcat(test, event.text.text);
            printf("%s\n", event.text.text);
            printf("%s\n", strcat(test, event.text.text));
            break;
        }
    }

    return quit;
}