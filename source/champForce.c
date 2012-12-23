#include "champForce.h"

ChampForce createChampForce(int x, int y, int rayon, int intensite, SDL_Surface* spriteAtt, SDL_Surface* spriteRep)
{
    ChampForce a = {};
    a.pos = (Point){x, y};
    a.rayon = rayon;
    a.intensite = intensite;
    if (intensite < 0)
        a.sprite = spriteAtt;
    else
        a.sprite = spriteRep;

    return a;

}

void affichChampForce(ChampForce a, SDL_Surface* screen)
{
    SDL_Rect rect;
    rect.x = a.pos.x - a.sprite->w/4;
    rect.y = a.pos.y - a.sprite->h*3/4;
    rect.w = a.sprite->w;
    rect.h = a.sprite->h;
    SDL_BlitSurface(a.sprite, NULL, screen, &rect);

    circleColor(screen, (Sint16)a.pos.x, (Sint16)a.pos.y, a.rayon, 0xffffffff);

}
