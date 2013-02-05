#ifndef _SHIP
#define _SHIP

#include "vector.h"
#include "SDL.h"

typedef struct Ship Ship;
struct Ship
{
    Vector totalForces;          // somme des forces qui s'exerce sur le vaisseau à chaque cycle
    Vector vitesse;              // vitesse du vaisseau, calculée à partir de la somme des forces
    Point pos;                   // position du vaisseau, modifiée par la vitesse
    SDL_Surface* spriteOriginal; // sprite de référence du vaisseau
    SDL_Surface* sprite;         // sprite orienté du vaisseau
    int rayon;                   // rayon du cercle de la hitbox
};

Ship Ship_Create(Point pos, SDL_Surface* sprite);
void resolveWallCollision(Ship* a, int w, int h);
void applyForces(Ship* ship);
void addForce(Ship* ship, Vector force);
void nextpos(Ship* ship);
void Ship_Turn(Ship* a);
void Ship_Draw(Ship a, SDL_Surface* screen);
void Ship_Debug(Ship a);

#endif // _SHIP
