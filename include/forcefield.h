#ifndef _FORCEFIELD
#define _FORCEFIELD

#include "vector.h"

#include "SDL_video.h"

#include <stdbool.h>

typedef struct Forcefield {

    Point pos;
    int rayon;
    int intensity;
    SDL_Surface* sprite;

} Forcefield;

Forcefield createForcefield(int x, int y, int rayon, int intensity, SDL_Surface* sprite);
bool isInForcefieldRange(Forcefield field, Point p);
Vector calculateForce(Forcefield field, Point pos);
Forcefield* findFieldNearby(Forcefield* tabField, int nbFields, int x, int y);
void drawForcefield(Forcefield a, SDL_Surface* screen);
void drawForcefields(Forcefield* tabField, int nb, SDL_Surface* screen);

#endif // _FORCEFIELD
