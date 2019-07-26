#include "../headerFiles/header.h"

int main(void)
{
    stGame *game = NULL;
    game = malloc(sizeof(stGame));

    game->screenSize.x = 640;
    game->screenSize.y = 480;
    game->pWindow = NULL;
    game->pRenderer = NULL;

    stImgInit *imgs[10];
    for (int i = 0; i < 10; i++)
    {
        imgs[i] = NULL;
        imgs[i] = malloc(sizeof(stImgInit *));
    }
    char *text[] = {"toto", "tata", "titi", "tutu", "tete"};

    for (int i = 0; i < 10; i++)
    {
        free(imgs[i]);
    }
    return 1;
}
