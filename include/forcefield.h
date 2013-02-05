#ifndef _FORCEFIELD
#define _FORCEFIELD

#include "vector.h"

#include "SDL_video.h"

#include <stdbool.h>

typedef struct Field {

    Point pos;
    int rayon;
    int intensity;
    SDL_Surface* sprite;

} Field;

Field Field_Create(int x, int y, int rayon, int intensity, SDL_Surface* sprite);
bool isInFieldRange(Field field, Point p);
Vector Field_GetForceAtPoint(Field field, Point pos);
Field* findFieldNearPoint(Field* tabField, int nbFields, int x, int y);
void Field_Draw(Field a, SDL_Surface* screen);
void Field_MultipleDraw(Field* tabField, int nb, SDL_Surface* screen);

#endif // _FORCEFIELD
