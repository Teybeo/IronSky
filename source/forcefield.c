#include "forcefield.h"

Forcefield createForcefield(int x, int y, int rayon, int intensity, SDL_Surface* spriteAtt, SDL_Surface* spriteRep)
{
    Forcefield a = {};
    a.pos = (Point){x, y};
    a.rayon = rayon;
    a.intensity = intensity;
    if (intensity < 0)
        a.sprite = spriteAtt;
    else
        a.sprite = spriteRep;

    return a;

}

bool isInForcefieldRange(Forcefield field, Point p)
{
    return distanceVect(createVect(field.pos, p)) < field.rayon;
}

Vector calculateForce(Forcefield field, Point pos)
{
    Vector normale = createVect(field.pos,  pos);
    float longueur = distanceVect(normale);
    divisVecScal(&normale, longueur);

    Vector force = normale;
    multVecScal(&force, field.intensity * 0.01/longueur);

    return force;
}

void drawForcefield(Forcefield a, SDL_Surface* screen)
{
    SDL_Rect rect;
    rect.x = a.pos.x - a.sprite->w/4;
    rect.y = a.pos.y - a.sprite->h*3/4;
    rect.w = a.sprite->w;
    rect.h = a.sprite->h;
    SDL_BlitSurface(a.sprite, NULL, screen, &rect);

    //circleColor(screen, (Sint16)a.pos.x, (Sint16)a.pos.y, a.rayon, 0xffffffff);

}
