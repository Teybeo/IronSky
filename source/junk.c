#include "junk.h"

#include "SDL.h"
#include "vecteur.h"
#include "SDL_gfxPrimitives.h"

Junk createJunk(int x, int y, SDL_Surface* sprite) {

    Junk a = {};
    a.pos.x = x + sprite->w/2.;
    a.pos.y = y + sprite->h/2.;
    a.take = 0;
    a.rayon = 13;
    a.sprite = sprite;

    return a;

}

void afficherDechet(Junk a, SDL_Surface* screen) {

    SDL_Rect pos;
    pos.x = a.pos.x - a.sprite->w/2;
    pos.y = a.pos.y - a.sprite->h/2;
    pos.w = a.sprite->w;
    pos.h = a.sprite->h;

    SDL_BlitSurface(a.sprite, 0, screen, &pos);

    circleColor(screen, a.pos.x, a.pos.y, a.rayon, 0xffff00ff);
}

bool takeJunk(Junk* junk, Point pos, int rayon)
{
    if (distanceVect( createVect(junk->pos, pos)) < (rayon + junk->rayon) && junk->take == 0)
    {
        junk->take = 1;
        return true;
    }

    return false;
}
