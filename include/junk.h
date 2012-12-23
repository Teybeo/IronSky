#ifndef _JUNK
#define _JUNK

#include "SDL.h"
#include "Point.h"

#include <stdbool.h>

typedef struct Junk
{
    SDL_Surface *sprite;//images utilisé pour le dechet
    Point pos; //position du dechet
    int take;
    int rayon;
} Junk;

Junk createJunk(int x, int y, SDL_Surface* sprite);
void afficherDechet(Junk a, SDL_Surface* screen);
bool takeJunk(Junk* junk, Point pos, int rayon);

#endif // _JUNK
