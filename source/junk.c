#include "junk.h"

#include "SDL.h"
#include "vector.h"
#include "SDL_gfxPrimitives.h"

Junk createJunk(Point pos, SDL_Surface* sprite) {

    Junk a = {};
    a.pos.x = pos.x + sprite->w/2.;
    a.pos.y = pos.y + sprite->h/2.;
    a.taken = false;
    a.rayon = 13;
    a.sprite = sprite;

    return a;

}

void drawJunk(Junk a, SDL_Surface* screen) {

    SDL_Rect pos;
    pos.x = a.pos.x - a.sprite->w/2;
    pos.y = a.pos.y - a.sprite->h/2;
    pos.w = a.sprite->w;
    pos.h = a.sprite->h;

    SDL_BlitSurface(a.sprite, 0, screen, &pos);

//    circleColor(screen, a.pos.x, a.pos.y, a.rayon, 0xffff00ff);
}

bool canTakeJunk(Junk junk, Point pos, int rayon)
{
    if (junk.taken == false && distance2Points(junk.pos, pos) < (rayon + junk.rayon) )
    {
        return true;
    }

    return false;
}

void setTakenJunk(Junk* junk, bool taken) {

    junk->taken = taken;
}

void drawAvailableJunks(Junk* tabJunk, int nb, SDL_Surface* screen)
{
    int i;
    for (i = 0 ; i < nb ; i++)
    {
        if (tabJunk[i].taken == false)
            drawJunk(tabJunk[i], screen);
    }

}
