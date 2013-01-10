#ifndef _SPACESHIP
#define _SPACESHIP

#include "vector.h"
#include "SDL.h"

typedef struct SpaceShip SpaceShip;
struct SpaceShip
{
    Vector totalForces;          // total des forces qui s'exerce sur le vaisseau à chaque cycle
    Vector vitesse;              // vitesse du vaisseau, calculée à partir du total des forces
    Point pos;                   // position du vaisseau, modifiée par la vitesse
    SDL_Surface* spriteOriginal; // sprite de référence du vaisseau
    SDL_Surface* sprite;         // sprite orienté du vaisseau
    int rayon;                   // rayon du cercle de la hitbox
};

SpaceShip createSpaceShip(int x0,int y0, SDL_Surface* sprite);
void applyForces(SpaceShip* spaceshipA);
void addForces(SpaceShip* spaceshipA, Vector force);
void nextpos(SpaceShip* spaceshipA);
void turnSpaceShip(SpaceShip* a);
void drawSpaceship(SpaceShip a, SDL_Surface* screen);
void debugSpaceship(SpaceShip a);

#endif // _SPACESHIP
