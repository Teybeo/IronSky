#ifndef _FORCEFIELD
#define _FORCEFIELD

#include "point.h"
#include "vector.h"

#include "SDL.h"

#include <stdbool.h>

typedef struct Forcefield {

    Point pos;
    int rayon;
    int intensity;
    SDL_Surface* sprite;

} Forcefield;

Forcefield createForcefield(int x, int y, int rayon, int intensity, SDL_Surface* spriteAtt, SDL_Surface* spriteRep);
bool isInForcefieldRange(Forcefield field, Point p);
Vector calculateForce(Forcefield field, Point pos);
void drawForcefield(Forcefield a, SDL_Surface* screen);

#endif // _FORCEFIELD
