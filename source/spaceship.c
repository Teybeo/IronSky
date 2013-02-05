#include "spaceship.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives.h"

#include <math.h>

Ship Ship_Create(Point pos, SDL_Surface* sprite)
{
    Ship ship;
    Vector vecteurNull;
    vecteurNull.x = 0;
    vecteurNull.y = 0;
    ship.rayon = 40 ; // 55
    ship.pos = pos;
    ship.vitesse = vecteurNull;
    ship.totalForces = vecteurNull;
    ship.spriteOriginal = sprite;
    ship.sprite = sprite;

    return ship;
}

void applyForces(Ship* ship)
{
    ship->vitesse.x += ship->totalForces.x * 100;
    ship->vitesse.y += ship->totalForces.y * 100;

    ship->totalForces.x = 0;
    ship->totalForces.y = 0;

}

void nextpos(Ship* ship)
{
    ship->pos.x += ship->vitesse.x * 100;
    ship->pos.y += ship->vitesse.y * 100;
}

void resolveWallCollision(Ship* a, int w, int h)
{
    if (a->pos.x - a->rayon < 0) // Gauche
    {
        a->vitesse.x *= -0.9;
        a->pos.x = a->rayon;
    }
    else if (a->pos.x + a->rayon > w) // Droite
    {
        a->vitesse.x *= -0.9;
        a->pos.x = w - a->rayon;
    }
    if (a->pos.y + a->rayon > h) // Bas
    {
        a->vitesse.y *= -0.9;
        a->pos.y = h - a->rayon;
    }
    else if (a->pos.y - a->rayon < 0) // Haut
    {
        a->vitesse.y *= -0.9;
        a->pos.y = a->rayon;
    }
}

void Ship_Turn(Ship* a) {

    float angle = atan2(-a->vitesse.y, a->vitesse.x) * 180/M_PI;

    if (a->sprite != NULL && a->sprite != a->spriteOriginal)
        SDL_FreeSurface(a->sprite);

//    printf("angle %f\n", angle);

    a->sprite = rotozoomSurface(a->spriteOriginal, -90+angle, 1, 1);

}

void Ship_Draw(Ship a, SDL_Surface* screen) {

    SDL_Rect rect;
    rect.x = a.pos.x - a.sprite->w/2;
    rect.y = a.pos.y - a.sprite->h/2;
    rect.w = a.sprite->w;
    rect.h = a.sprite->h;

    SDL_BlitSurface(a.sprite, 0, screen, &rect);

//    circleColor(screen, a.pos.x, a.pos.y, a.rayon, 0xff0000ff);
//    Sint16 vx = (Sint16)(a.vitesse.x*1000);
//    Sint16 vy = (Sint16)(a.vitesse.y*1000);

//    lineColor(screen, (Sint16)a.pos.x, (Sint16)a.pos.y, (Sint16)a.pos.x+(vx), (Sint16)a.pos.y+(vy), 0xff0000ff);
//    rectangleColor(screen, rect.x, rect.y, rect.x+rect.w, rect.y+rect.h, 0xff0000ff);

}

void addForce(Ship* ship, Vector force)
{
    addVectors(&ship->totalForces, force);
}

void Ship_Debug(Ship a) {

    printf("Pos x %f   y %f\n", a.pos.x, a.pos.y);
    printf("Vit x %f   y %f\n", a.vitesse.x, a.vitesse.y);

}
