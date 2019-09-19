
#include "../../headerFiles/game/game.h" 

stMenu *menu_init(SDL_Window *pWindow, SDL_Renderer *pRenderer) {
    stMenu *menu = {0};
    menu = malloc(sizeof(stMenu));
    char *path = "assets/Menu/logo.png";
    menu->surfaceMenu = IMG_Load(path);
    if (!menu->surfaceMenu) {
        fprintf(stderr, "Erreur au chargement de l'image : %s,%s\n", path,
                IMG_GetError());
        menu_destroy_2(menu);
    }
    else {
        menu->textureMenu = SDL_CreateTextureFromSurface(
            pRenderer, menu->surfaceMenu);
        if (!menu->textureMenu) {
            fprintf(stderr, "Erreur au chargement de la texture : %s,%s\n",
                    path, SDL_GetError());
            menu_destroy_2(menu);
        }
        SDL_FreeSurface(menu->surfaceMenu);
    }
    TTF_Init();
    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    menu->pWindow = pWindow;
    menu->pRenderer = pRenderer;
    menu->police1 = TTF_OpenFont(PATHFGRAFITI, 70);
    menu->police2 = TTF_OpenFont(PATHFNEON, 45);
    TTF_SetFontOutline(menu->police2, 1);
    menu->pTextChoix = font_load(menu, menu->police2, TXTSURFCHOIX);
    menu->pTextHostname = font_load(menu, menu->police1, TXTSURFHOSTNAME);
    menu->pTextPortname = font_load(menu, menu->police1, TXTSURFPORTNAME);
    menu->pTextWelcome = font_load(menu, menu->police1, TXTWELCOMESERVEUR);
    menu->pTextheberger = font_load_shaded(menu, menu->police2, TXTHEBERGER);
    menu->pTextRejoindre = font_load_shaded(menu, menu->police2, TXTREJOINDRE);
    SDL_StartTextInput();

    return menu;
}

void menu_event(SDL_Event event, int *step, char **currentText, char *hostname, char *port, int socket_target) {
    while (SDL_PollEvent(&event) != 0) {
        SDL_Rect hebergerClick = {550, 400, 500, 100};
        SDL_Rect rejoindreClick = {550, 600, 500, 100};
        int xClick = event.button.x;
        int yClick = event.button.y;
        switch (event.type) {
        case (SDL_QUIT):
            *step = -1;
        case (SDL_TEXTINPUT):
            strcat(*currentText, event.text.text);
            break;
        case (SDL_MOUSEBUTTONUP):
            switch (event.button.button) {
            case (SDL_BUTTON_LEFT):
                if (xClick >= hebergerClick.x && xClick <= hebergerClick.x + hebergerClick.w && yClick >= hebergerClick.y && yClick <= hebergerClick.y + hebergerClick.h) {
                    strcpy(*currentText, "1");
                    (*step)++;
                    *currentText = hostname;
                }
                else if (xClick >= rejoindreClick.x && xClick <= rejoindreClick.x + rejoindreClick.w && yClick >= rejoindreClick.y && yClick <= rejoindreClick.y + rejoindreClick.h) {
                    strcpy(*currentText, "2");
                    (*step)++;
                    *currentText = hostname;
                }
                break;
            }
            break;
        case (SDL_KEYDOWN):
            switch (event.key.keysym.sym) {
            case SDLK_BACKSPACE:
                strcpy(*currentText, "");
                break;
            case SDLK_RETURN:
                (*step)++;
                if (*step == 1) {
                    *currentText = hostname;
                }
                if (*step == 2) {
                    *currentText = port;
                }
                break;
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_RIGHT:
            case SDLK_LEFT:
            case SDLK_SPACE:
                send_key(event.key.keysym.sym, socket_target);
                break;
            }
        }
    }
}

void menu_destroy_2(stMenu *menu) {
    if (menu) {
        TTF_CloseFont(menu->police1);
        TTF_CloseFont(menu->police2);
        SDL_DestroyWindow(menu->pWindow);
        SDL_DestroyRenderer(menu->pRenderer);
        free(menu);
    }
}
