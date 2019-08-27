
#include "../headerFiles/menu.h"

SDL_Texture *font_load(stMenu *menu, TTF_Font *police, char* content) {
    SDL_Color noir = {0, 0, 0};

    menu->surface = TTF_RenderText_Blended(police, content, noir);

    if (!menu->surface) {
        fprintf(stderr, "Erreur au chargement du text : %s\n", IMG_GetError());
        menu_destroy_2(menu);
    } else {
        menu->texture = SDL_CreateTextureFromSurface(menu->pRenderer, menu->surface);

        if (!menu->texture) {
            fprintf(stderr, "Erreur au chargement de la texture : %s\n", SDL_GetError());
            menu_destroy_2(menu);
        }

        SDL_FreeSurface(menu->surface);

        return menu->texture;
    }

}