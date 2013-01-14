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
    lev.nbJunks = rand() % 500;

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


void loadLevel(int IDlevel, Junk** tabJunk, int* nbJunks, SpaceShip* spaceship, SDL_Surface* junkSprite, SDL_Surface* spaceshipSprite)
{
    char chemin[20] = "";
    sprintf(chemin, "Niveaux/%d.niveau", IDlevel);

    FILE* fichier = fopen(chemin, "rb");
    if (fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s", chemin);
        return;
    }

    fread(nbJunks, sizeof(int), 1, fichier);

    // Récupération du tableau de Points
    Point* tabPosJunk = malloc(*nbJunks * sizeof(Point));
    fread(tabPosJunk, sizeof(Point), *nbJunks, fichier);

    // Création du tableau de Junks à partir des points récupérés
    *tabJunk = malloc(*nbJunks * sizeof(Junk));
    int i;
    for( i = 0; i < *nbJunks; i++)
    {
        (*tabJunk)[i] = createJunk(tabPosJunk[i].x, tabPosJunk[i].y, junkSprite);
    }

    // Destruction du tableau de points
    free(tabPosJunk);

    Point depart = {};

    fread(&depart, sizeof(Point), 1, fichier);

    *spaceship = createSpaceShip(depart.x, depart.y, spaceshipSprite);

    fclose(fichier);

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
