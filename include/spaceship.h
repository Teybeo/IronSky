#ifndef _SPACESHIP
#define _SPACESHIP

#include "vecteur.h"
#include "SDL.h"

typedef struct SpaceShip SpaceShip;
struct SpaceShip
{
    Vecteur totalForces;// total des forces qui s'exerce sur le vaisseau
    Vecteur vitesse;//vitesse du vaisseau a un instant T
    Point pos;// position du vaisseau
    SDL_Surface* spriteOriginal;// sprite du vaisseau
    SDL_Surface* sprite;// sprite du vaisseau
    int rayon;
};

SpaceShip createSpaceShip(int x0,int y0, SDL_Surface* sprite);
void appliqueForces(SpaceShip* spaceshipA);
void addForces(SpaceShip* spaceshipA, Vecteur force);
void nextpos(SpaceShip* spaceshipA);
void turnSpaceShip(SpaceShip* a);
void afficheSpaceship(SpaceShip a, SDL_Surface* screen);
void debugSpaceship(SpaceShip a);

#endif // SPACESHIP
