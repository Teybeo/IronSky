#ifndef VECTEUR
#define VECTEUR

#include "point.h"

typedef struct Vecteur Vecteur;
struct Vecteur
{
    float x;
    float y;
};

void addVecteurs(Vecteur* a, Vecteur b);
float distanceVect(Vecteur v);
Vecteur createVect(Point a, Point b);
void multVec(Vecteur* a, Vecteur b);
void multVecScal(Vecteur* a, float s);
void divisVecScal(Vecteur* a, float s);

#endif // VECTEUR

