#include "level.h"

#include "SDL_video.h"
#include <stdio.h>
#include <stdlib.h>

FILE* openLevelByID(int ID, const char* mode);

void loadLevel(int IDlevel, Game* g, SDL_Surface* junkSprite, SDL_Surface* spaceshipSprite)
{
    FILE* fichier = openLevelByID(IDlevel, "rb");

    fread(&g->nbJunks, sizeof(int), 1, fichier);

    //Récupération du tableau de Points
    Point* tabPosJunk = malloc(g->nbJunks * sizeof(Point));
    fread(tabPosJunk, sizeof(Point), g->nbJunks, fichier);

    // Création du tableau de Junks à partir des points récupérés
    g->tabJunk = malloc(g->nbJunks * sizeof(Junk));
    int i;
    for( i = 0; i < g->nbJunks; i++)
    {
        g->tabJunk[i] = createJunk(tabPosJunk[i].x, tabPosJunk[i].y, junkSprite);
    }

    // Destruction du tableau de points
    free(tabPosJunk);

    Point depart = {};
    fread(&depart, sizeof(Point), 1, fichier);

    g->player = createSpaceShip(depart.x, depart.y, spaceshipSprite);

    fread(&g->nbAttractors, sizeof(int), 1, fichier);

    fread(&g->nbRepulsors, sizeof(int), 1, fichier);

    fclose(fichier);

}

void generateRandomLevel(int w, int h, int IDLevel)
{
    // Création d'un niveau aléatoirement
    int nbJunks = rand() % 500;
    int nbAttractors = rand() % 7;
    int nbRepulsors = 7 - nbAttractors;

    // créer un nouveau tableau contenant exclusivement les positions des dechets
    Point* tabPosJunk = malloc(nbJunks * sizeof(Point));
    int i;
    for(i = 0; i < nbJunks; i++)
    {
        tabPosJunk[i].x = rand() % (w - 55);
        tabPosJunk[i].y = rand() % (h - 55);
    }

    Point depart = { rand() % w, rand() % h };

    FILE* fichier = openLevelByID(IDLevel, "wb");

    fwrite(&nbJunks, sizeof(int), 1, fichier);

    fwrite(tabPosJunk, sizeof(Point), nbJunks, fichier);

    fwrite(&depart, sizeof(Point), 1, fichier);

    fwrite(&nbAttractors, sizeof(int), 1, fichier);

    fwrite(&nbRepulsors, sizeof(int), 1, fichier);

    fclose(fichier);
}

FILE* openLevelByID(int ID, const char* mode) {

    char chemin[20] = "";
    sprintf(chemin, "Niveaux/%d.niveau", ID);

    FILE* fichier = fopen(chemin, mode);
    if (fichier == NULL)
    {
        printf("Erreur a l ouverture de: %s en mode %s\n", chemin, mode);
        exit(EXIT_FAILURE);
    }

    return fichier;

}
