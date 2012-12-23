#include "level.h"

#include "junk.h"
#include "SDL_video.h"
#include <stdio.h>
#include <stdlib.h>

Level createLevel(int nbJunk, Point* tabPosJunk, Point depart) {

    Level a = {};
    a.nbJunk = nbJunk;
    a.tabPosJunk = tabPosJunk;
    a.depart = depart;

    return a;
}

Level generateLevel(int w, int h)
{
    Level lev = {};

    // Création d'un niveau aléatoirement
    lev.nbJunk = rand() % 2000;

    //creer un nouveau tableau contenant exclusivement les positions des dechets
    lev.tabPosJunk = malloc(lev.nbJunk * sizeof(Point));
    int i;
    for(i = 0; i < lev.nbJunk; i++)
    {
        lev.tabPosJunk[i].x = rand() % (w - 55);
        lev.tabPosJunk[i].y = rand() % (h - 55);
    }

    lev.depart.x = rand() % w;;
    lev.depart.y = rand() % h;;

    return lev;
}

void saveLevel(Level a) {

    FILE* fichier = fopen("test.niveau", "wb");
    if (fichier == NULL)
    {
        puts("Probleme ouverture de test.niveau");
        return;
    }

    fwrite(&a.nbJunk, sizeof(int), 1, fichier);

    fwrite(a.tabPosJunk, sizeof(Point), a.nbJunk, fichier);

    fwrite(&a.depart, sizeof(Point), 1, fichier);

    fclose(fichier);

}

void buildLevel(Level lev, Junk** tabJunk, SpaceShip* spaceship, SDL_Surface* spriteEcrou, SDL_Surface* spriteSpaceship) {

    *tabJunk = malloc(lev.nbJunk * sizeof(Junk));
    int i;
    for( i = 0; i < lev.nbJunk; i++)
    {
        (*tabJunk)[i] = createJunk(lev.tabPosJunk[i].x, lev.tabPosJunk[i].y, spriteEcrou);
    }

    *spaceship = createSpaceShip(lev.depart.x, lev.depart.y, spriteSpaceship);

}

Level chargeLevel(char* chemin) {

    Level a = {};

    FILE* fichier = fopen(chemin, "rb");
    if (fichier == NULL)
    {
        puts("Probleme ouverture de test.niveau");
        return a;
    }

    fread(&a.nbJunk, sizeof(int), 1, fichier);

    a.tabPosJunk = malloc(a.nbJunk * sizeof(Point));

    fread(a.tabPosJunk, sizeof(Point), a.nbJunk, fichier);

    fread(&a.depart, sizeof(Point), 1, fichier);

    fclose(fichier);

    return a;
}
