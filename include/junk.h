#ifndef _JUNK
#define _JUNK

#include "SDL.h"
#include "vector.h"

#include <stdbool.h>

typedef struct Junk
{
    SDL_Surface *sprite; // image utilisée pour le dechet
    Point pos;           // position du dechet
    bool taken;          // indique si le dechet a été ramassé
    int rayon;           // rayon du cercle de hitbox

} Junk;

Junk Junk_Create(Point pos, SDL_Surface* sprite);
void Junk_Draw(Junk a, SDL_Surface* screen);
void Junk_MultipleDraw(Junk* tabJunk, int nb, SDL_Surface* screen);
bool canTakeJunk(Junk junk, Point pos, int rayon);
void setTakenJunk(Junk* junk, bool taken);

#endif // _JUNK
