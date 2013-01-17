#ifndef _VECTOR
#define _VECTOR

typedef struct Vector {

    float x;
    float y;

} Vector;

typedef Vector Point;

void addVectors(Vector* a, Vector b);
float distanceVect(Vector v);
float distance2Points(Point a, Point b);
Vector createVect(Point a, Point b);
void multVec(Vector* a, Vector b);
void multVecScal(Vector* a, float s);
void divisVecScal(Vector* a, float s);

#endif // _VECTOR

