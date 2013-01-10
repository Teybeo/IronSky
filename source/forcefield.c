#include "forcefield.h"

ForceField createForceField(int x, int y, int rayon, int intensity, SDL_Surface* spriteAtt, SDL_Surface* spriteRep)
{
    ForceField a = {};
    a.pos = (Point){x, y};
    a.rayon = rayon;
    a.intensity = intensity;
    if (intensity < 0)
        a.sprite = spriteAtt;
    else
        a.sprite = spriteRep;

    return a;

}

void drawForceField(ForceField a, SDL_Surface* screen)
{
    SDL_Rect rect;
    rect.x = a.pos.x - a.sprite->w/4;
    rect.y = a.pos.y - a.sprite->h*3/4;
    rect.w = a.sprite->w;
    rect.h = a.sprite->h;
    SDL_BlitSurface(a.sprite, NULL, screen, &rect);

    //circleColor(screen, (Sint16)a.pos.x, (Sint16)a.pos.y, a.rayon, 0xffffffff);

}
