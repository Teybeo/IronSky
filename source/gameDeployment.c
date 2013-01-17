#include "gameDeployment.h"

void gameDeploymentDraw(GameDeployment m) {

    // draw background
    SDL_BlitSurface(m.background, NULL, m.screen, NULL);

    // draw all junks
    drawAvailableJunks(m.g->tabJunk, m.g->nbJunks, m.screen);

    // draw all attractors
    drawForcefields(m.g->tabAttractor, m.nbCurrentAtt, m.screen);

    // draw all repulsors
    drawForcefields(m.g->tabRepulsor, m.nbCurrentRep, m.screen);

    // draw spaceship
    drawSpaceship(m.g->player, m.screen);

    // draw UI
    drawButton(m.attrac, m.screen);
    drawButton(m.repuls, m.screen);

    SDL_Flip(m.screen);

}

Forcefield* findFieldNearby(GameDeployment m, int x, int y);

void gameDeploymentEvent(GameDeployment* m, SDL_Event ev) {

    switch (ev.type)
    {
    case SDL_KEYDOWN:

        // Mise en pause
        if (ev.key.keysym.sym == SDLK_ESCAPE)
            m->pause = true;

        // Passage en mode jeu
        if (ev.key.keysym.sym == SDLK_SPACE)
            m->game = true;

    break;

    case SDL_MOUSEMOTION:

        updateButtonState(&m->attrac, ev.motion.x, ev.motion.y);
        updateButtonState(&m->repuls, ev.motion.x, ev.motion.y);

        if (m->selection != NULL)
            addVectors((Vector*)&m->selection->pos, (Vector) {ev.motion.xrel, ev.motion.yrel});

    break;

    case SDL_MOUSEBUTTONDOWN:

        if (ev.button.button == SDL_BUTTON_LEFT)
        {
            if (m->selection == NULL)
                m->selection = findFieldNearby(*m, ev.motion.x, ev.motion.y);

            if (m->selection == NULL)
            {
                puts("Nothing found !");
                // On ajoute un attractor au tableau
                if (isInBox(m->attrac.rect, ev.button.x, ev.button.y) == true && m->nbCurrentAtt < m->g->nbAttractors)
                {
                    m->g->tabAttractor[m->nbCurrentAtt] = createForcefield(ev.button.x, ev.button.y, 100, -1, m->attSprite);
                    m->selection = &m->g->tabAttractor[m->nbCurrentAtt];
                    m->nbCurrentAtt++;
                    puts("AjoutAtt !");
                }

                // On ajoute un repulsor au tableau
                if (isInBox(m->repuls.rect, ev.button.x, ev.button.y) == true && m->nbCurrentRep < m->g->nbRepulsors)
                {
                    m->g->tabRepulsor[m->nbCurrentRep] = createForcefield(ev.button.x, ev.button.y, 100, 1, m->repSprite);
                    m->selection = &m->g->tabRepulsor[m->nbCurrentRep];
                    m->nbCurrentRep++;
                    puts("AjoutRep !");
                }
            }

        }
    break;

    case SDL_MOUSEBUTTONUP:

        if (ev.button.button == SDL_BUTTON_LEFT)
            m->selection = NULL;

    break;

    }

}

GameDeployment gameDeploymentInit(SDL_Surface* screen, Game* g, SDL_Surface* attSprite, SDL_Surface* repSprite) {

    GameDeployment m = {};

    m.g = g;
    m.screen = screen;
    m.background = g->background;
    m.attSprite = attSprite;
    m.repSprite = repSprite;

    m.pause = false;
    m.game = false;

    m.attrac = createButton(100, 100, 100, 100, 0x5321ff, 0x9921ff);
    m.repuls = createButton(100, 300, 100, 100, 0x5321ff, 0x9921ff);

    m.selection = NULL;

    if (g->tabAttractor == NULL)
    {
        m.g->tabAttractor = malloc(sizeof(Forcefield) * m.g->nbAttractors);
        m.nbCurrentAtt = 0;
    }
    else
        m.nbCurrentAtt = g->nbAttractors;

    if (g->tabRepulsor == NULL)
    {
        m.g->tabRepulsor = malloc(sizeof(Forcefield) * m.g->nbRepulsors);
        m.nbCurrentRep = 0;
    }
    else
        m.nbCurrentRep = g->nbRepulsors;

    return m;
}

void resetInputGameDeployment(GameDeployment* g) {

    g->pause = false;
    g->game = false;

}

Forcefield* findFieldNearby(GameDeployment m, int x, int y)
{
    int i;

    for (i = 0 ; i < m.nbCurrentAtt ; i++ )
    {
        if (distanceVect(createVect((Point){x, y}, m.g->tabAttractor[i].pos) ) < 15)
            return &m.g->tabAttractor[i];
    }

    for (i = 0 ; i < m.nbCurrentRep ; i++ )
    {
        if (distanceVect(createVect((Point){x, y}, m.g->tabRepulsor[i].pos) ) < 15)
            return &m.g->tabRepulsor[i];
    }
    return NULL;

}
