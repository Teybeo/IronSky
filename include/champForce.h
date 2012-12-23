#ifndef CHAMPFORCE
#define CHAMPFORCE

#include "point.h"

#include "SDL.h"

typedef struct ChampForce {

    Point pos;
    int rayon;
    int intensite;
    SDL_Surface* sprite;

} ChampForce;

ChampForce createChampForce(int x, int y, int rayon, int intensite, SDL_Surface* spriteAtt, SDL_Surface* spriteRep);
void affichChampForce(ChampForce a, SDL_Surface* screen);

#endif // CHAMPFORCE
