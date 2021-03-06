#include "stateDeployment.h"

#include "app.h"

void Deployment_Draw(State* state) {

    Deployment* deployment = (Deployment*)state;

    // draw background
    SDL_BlitSurface(deployment->background, NULL, state->screen, NULL);

    // draw all junks
    Junk_MultipleDraw(deployment->gameData->junks, deployment->gameData->nbJunks, state->screen);

    // draw all attractors
    Field_MultipleDraw(deployment->gameData->attractors, deployment->gameData->nbCurrentAtt, state->screen);

    // draw all repulsors
    Field_MultipleDraw(deployment->gameData->repulsors, deployment->gameData->nbCurrentRep, state->screen);

    // draw spaceship
    Ship_Draw(deployment->gameData->player, state->screen);

    // draw UI
    Button_Draw(deployment->attrac, state->screen);
    Button_Draw(deployment->repuls, state->screen);

    SDL_Flip(state->screen);

}

void Deployment_Event(State* state, SDL_Event ev) {

    Deployment* deployment = (Deployment*)state;

    switch (ev.type)
    {
    case SDL_KEYDOWN:

        // Mise en pause
        if (ev.key.keysym.sym == SDLK_ESCAPE)
            setCurrentState(state->appRef, getPauseState(state->appRef));

        // Il faut avoir placé tous les fields pour pouvoir passer en jeu !
        if (ev.key.keysym.sym == SDLK_SPACE
            && deployment->gameData->nbCurrentAtt == deployment->gameData->nbAttractors
            && deployment->gameData->nbCurrentRep == deployment->gameData->nbRepulsors  )
            setCurrentState(state->appRef, getPlayState(state->appRef));

    break;

    case SDL_MOUSEMOTION:

        Button_UpdateState(&deployment->attrac, ev.motion.x, ev.motion.y);
        Button_UpdateState(&deployment->repuls, ev.motion.x, ev.motion.y);

        // On déplace le field sélectionné en fonction de la souris
        if (deployment->selection != NULL)
            addVectors((Vector*)&deployment->selection->pos, (Vector) {ev.motion.xrel, ev.motion.yrel});

    break;

    case SDL_MOUSEBUTTONDOWN:

        if (ev.button.button == SDL_BUTTON_LEFT)
        {
            // On essaie d'attraper un attractor
            if (deployment->selection == NULL)
                deployment->selection = findFieldNearPoint(deployment->gameData->attractors, deployment->gameData->nbCurrentAtt, ev.motion.x, ev.motion.y);

            // On essaie d'attraper un repulsor
            if (deployment->selection == NULL)
                deployment->selection = findFieldNearPoint(deployment->gameData->repulsors, deployment->gameData->nbCurrentRep, ev.motion.x, ev.motion.y);

            if (deployment->selection == NULL)
            {
                // On déploie un nouvel attractor
                if (isInBox(deployment->attrac.rect, ev.button.x, ev.button.y) == true && deployment->gameData->nbCurrentAtt < deployment->gameData->nbAttractors)
                {
                    deployment->gameData->attractors[deployment->gameData->nbCurrentAtt] = Field_Create(ev.button.x, ev.button.y, 100, -1, deployment->gameData->sprites[ATTRACTOR]);
                    deployment->selection = &deployment->gameData->attractors[deployment->gameData->nbCurrentAtt];
                    deployment->gameData->nbCurrentAtt++;
                    puts("AjoutAtt !");
                }

                // On déploie un nouveau repulsor
                if (isInBox(deployment->repuls.rect, ev.button.x, ev.button.y) == true && deployment->gameData->nbCurrentRep < deployment->gameData->nbRepulsors)
                {
                    deployment->gameData->repulsors[deployment->gameData->nbCurrentRep] = Field_Create(ev.button.x, ev.button.y, 100, 1, deployment->gameData->sprites[REPULSOR]);
                    deployment->selection = &deployment->gameData->repulsors[deployment->gameData->nbCurrentRep];
                    deployment->gameData->nbCurrentRep++;
                    puts("AjoutRep !");
                }
            }

        }
    break;

    case SDL_MOUSEBUTTONUP:

        // On relache le field sélectionné
        if (ev.button.button == SDL_BUTTON_LEFT)
            deployment->selection = NULL;

    break;

    }

}

void Deployment_Logic(State* state) {

}

Deployment Deployment_Create(App* appRef, GameData* g) {

    Deployment m = {};

    m.state = createState(appRef, &Deployment_Event, &Deployment_Logic, &Deployment_Draw, "Deployment");
    m.gameData = g;

    m.background = g->sprites[BACKGROUND];

    m.attrac = Button_Create(100, 100, 100, 100, 0x5321ff, 0x9921ff);
    m.repuls = Button_Create(100, 300, 100, 100, 0x5321ff, 0x9921ff);

    m.selection = NULL;

    return m;
}



