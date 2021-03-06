#include "field.h"

Field Field_Create(int x, int y, int rayon, int intensity, SDL_Surface* sprite)
{
    Field a = {};
    a.pos = (Point){x, y};
    a.rayon = rayon;
    a.intensity = intensity;
    a.sprite = sprite;

    return a;

}

bool isInFieldRange(Field field, Point p)
{
    return distance2Points(field.pos, p) < field.rayon;
}

Vector Field_GetForceAtPoint(Field field, Point pos)
{
    Vector normale = createVect(field.pos,  pos);
    float longueur = distanceVect(normale);
    divisVecScal(&normale, longueur);

    Vector force = normale;
    multVecScal(&force, field.intensity * 0.01/longueur);

    return force;
}

Field* findFieldNearPoint(Field* tabField, int nbFields, int x, int y)
{
    int i;

    for (i = 0 ; i < nbFields ; i++ )
    {
        if (distance2Points((Point){x, y}, tabField[i].pos) < 15)
            return &tabField[i];
    }

    return NULL;
}

void Field_Draw(Field a, SDL_Surface* screen)
{
    SDL_Rect rect;
    rect.x = a.pos.x - a.sprite->w/4;
    rect.y = a.pos.y - a.sprite->h*3/4;
    rect.w = a.sprite->w;
    rect.h = a.sprite->h;
    SDL_BlitSurface(a.sprite, NULL, screen, &rect);

    //circleColor(screen, (Sint16)a.pos.x, (Sint16)a.pos.y, a.rayon, 0xffffffff);

}

void Field_MultipleDraw(Field* tabField, int nb, SDL_Surface* screen)
{
    int i;
    for (i = 0 ; i < nb ; i++ )
        Field_Draw(tabField[i], screen);

}
