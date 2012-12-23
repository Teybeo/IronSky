#include "vecteur.h"

#include <math.h>

void addVecteurs(Vecteur* a, Vecteur b) {

    a->x += b.x;
    a->y += b.y;

}

Vecteur createVect(Point a, Point b)
{
    Vecteur res;
    res.x = b.x - a.x;
    res.y = b.y - a.y;
    return res;
}

float distanceVect(Vecteur v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

void multVec(Vecteur* a, Vecteur b) {

    a->x *= b.x;
    a->y *= b.y;

}

void multVecScal(Vecteur* a, float s) {

    a->x *= s;
    a->y *= s;
}

void divisVecScal(Vecteur* a, float s) {

    a->x /= s;
    a->y /= s;
}

