#ifndef _VECTOR
#define _VECTOR

#include "point.h"

typedef struct Vector Vector;
struct Vector
{
    float x;
    float y;
};

void addVectors(Vector* a, Vector b);
float distanceVect(Vector v);
Vector createVect(Point a, Point b);
void multVec(Vector* a, Vector b);
void multVecScal(Vector* a, float s);
void divisVecScal(Vector* a, float s);

#endif // _VECTOR

