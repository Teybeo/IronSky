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

Junk createJunk(int x, int y, SDL_Surface* sprite);
void drawJunk(Junk a, SDL_Surface* screen);
void drawAvailableJunks(Junk* tabJunk, int nb, SDL_Surface* screen);
bool canTakeJunk(Junk junk, Point pos, int rayon);
void setTakenJunk(Junk* junk, bool taken);

#endif // _JUNK
