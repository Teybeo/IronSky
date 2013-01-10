#ifndef _FORCEFIELD
#define _FORCEFIELD

#include "point.h"

#include "SDL.h"

typedef struct ForceField {

    Point pos;
    int rayon;
    int intensity;
    SDL_Surface* sprite;

} ForceField;

ForceField createForceField(int x, int y, int rayon, int intensite, SDL_Surface* spriteAtt, SDL_Surface* spriteRep);
void drawForceField(ForceField a, SDL_Surface* screen);

#endif // _FORCEFIELD
