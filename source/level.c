#include "level.h"

#include "junk.h"
#include "SDL_video.h"
#include <stdio.h>
#include <stdlib.h>

Level createLevel(int nbJunks, Point* tabPosJunk, Point depart) {

    Level a = {};
    a.nbJunks = nbJunks;
    a.tabPosJunk = tabPosJunk;
    a.depart = depart;

    return a;
}

Level generateLevel(int w, int h)
{
    Level lev = {};

    // Création d'un niveau aléatoirement
    lev.nbJunks = rand() % 2000;

    //creer un nouveau tableau contenant exclusivement les positions des dechets
    lev.tabPosJunk = malloc(lev.nbJunks * sizeof(Point));
    int i;
    for(i = 0; i < lev.nbJunks; i++)
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

    fwrite(&a.nbJunks, sizeof(int), 1, fichier);

    fwrite(a.tabPosJunk, sizeof(Point), a.nbJunks, fichier);

    fwrite(&a.depart, sizeof(Point), 1, fichier);

    fclose(fichier);

}

void loadLevel(Level lev, Junk** tabJunk, int* nbJunks, SpaceShip* spaceship, SDL_Surface* junkSprite, SDL_Surface* spaceshipSprite)
{

    *nbJunks = lev.nbJunks;
    *tabJunk = malloc(lev.nbJunks * sizeof(Junk));
    int i;
    for( i = 0; i < lev.nbJunks; i++)
    {
        (*tabJunk)[i] = createJunk(lev.tabPosJunk[i].x, lev.tabPosJunk[i].y, junkSprite);
    }

    *spaceship = createSpaceShip(lev.depart.x, lev.depart.y, spaceshipSprite);

}

Level openFileLevel(char* chemin) {

    Level a = {};

    FILE* fichier = fopen(chemin, "rb");
    if (fichier == NULL)
    {
        puts("Probleme ouverture de test.niveau");
        return a;
    }

    fread(&a.nbJunks, sizeof(int), 1, fichier);

    a.tabPosJunk = malloc(a.nbJunks * sizeof(Point));

    fread(a.tabPosJunk, sizeof(Point), a.nbJunks, fichier);

    fread(&a.depart, sizeof(Point), 1, fichier);

    fclose(fichier);

    return a;
}
