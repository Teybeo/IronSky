#include <SDL.h>
#include "SDL_image.h"

SDL_Surface* memoryImg(char* nom)
{
    /* Variables SDL */
    SDL_Surface *var, *var2;
    /* Chargement de l'image */
    var = IMG_Load(nom);

    if(var == NULL)
    {
        printf("\nImpossible d'ouvrir : %s",nom);
        exit(EXIT_FAILURE);
    }

    /*Convertion */
    var2 = SDL_DisplayFormatAlpha(var);
    SDL_FreeSurface(var);

    return var2;
}
