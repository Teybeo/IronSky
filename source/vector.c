#include "vector.h"

#include <math.h>

void addVectors(Vector* a, Vector b) {

    a->x += b.x;
    a->y += b.y;

}

Vector createVect(Point a, Point b)
{
    Vector res;
    res.x = b.x - a.x;
    res.y = b.y - a.y;
    return res;
}

float distanceVect(Vector v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

void multVec(Vector* a, Vector b) {

    a->x *= b.x;
    a->y *= b.y;

}

void multVecScal(Vector* a, float s) {

    a->x *= s;
    a->y *= s;
}

void divisVecScal(Vector* a, float s) {

    a->x /= s;
    a->y /= s;
}

