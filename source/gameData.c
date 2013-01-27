#include "gameData.h"

#include "fonctionCSDL.h"

#include "SDL_video.h"

#include <stdio.h>
#include <stdlib.h>

FILE* openLevelByID(int ID, const char* mode);

void loadLevel(GameData* g, int IDlevel)
{
    FILE* fichier = openLevelByID(IDlevel, "rb");

    fread(&g->nbJunks, sizeof(int), 1, fichier);

    // Création du tableau de Junks à partir des points récupérés
    g->junks = malloc(g->nbJunks * sizeof(Junk));

    Point posJunk = {};
    int i;

    for( i = 0; i < g->nbJunks; i++)
    {
        fread(&posJunk, sizeof(Point), 1, fichier);
        g->junks[i] = createJunk(posJunk, g->sprites[JUNK_A + rand() % 2]);
    }

    fread(&g->spawnPos, sizeof(Point), 1, fichier);
    g->player = createSpaceShip(g->spawnPos, g->sprites[SHIP]);

    fread(&g->nbAttractors, sizeof(int), 1, fichier);
    fread(&g->nbRepulsors, sizeof(int), 1, fichier);

    g->nbCurrentAtt = 0;
    g->nbCurrentRep = 0;

    g->attractors = malloc(sizeof(Forcefield) * g->nbAttractors);
    g->repulsors = malloc(sizeof(Forcefield) * g->nbRepulsors);

    fclose(fichier);

}

// On remet en visible tous les junks et on replace le vaisseau
void prepareGame(GameData* g) {

    int i;
    for (i = 0 ; i < g->nbJunks ; i++ )
        setTakenJunk(&g->junks[i], false);

    SDL_FreeSurface(g->player.sprite);
    g->player = createSpaceShip(g->spawnPos, g->sprites[SHIP]);

}

void loadGameSprites(GameData* g) {

    g->sprites = malloc( sizeof(SDL_Surface*) * NB_SPRITES );

    g->sprites[SHIP] = memoryImg("image/spaceshipE.png");
    g->sprites[JUNK_A] = memoryImg("image/junkA.png");
    g->sprites[JUNK_B] = memoryImg("image/junkC.png");
    g->sprites[BACKGROUND] = memoryImg("image/background.png");
    g->sprites[ATTRACTOR] = memoryImg("image/itemA.png");
    g->sprites[REPULSOR] = memoryImg("image/itemR.png");

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

    free(tabPosJunk);

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
