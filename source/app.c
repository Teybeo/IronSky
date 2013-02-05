#include "app.h"

#include "state.h"
#include "stateMenu.h"
#include "stateLevelMenu.h"
#include "statePlay.h"
#include "stateDeployment.h"
#include "statePause.h"
#include "gameData.h"

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct App {

    SDL_Surface* screen;    // surface affichée à l'écran
    State* current;         // état actuel du programme
    State* precedent;       // état précédent du programme
    Menu menu;
    LevelMenu levelMenu;
    Play play;
    Pause pause;
    Deployment deployment;
    GameData gameData;
    bool done;               // indique l'arrêt du programme

} App;

unsigned int updateChrono();

void App_Event(App* app) {

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            app->done = true;

        app->current->event(app->current, event);

    }

}

void App_Logic(App* app) {

    app->current->logic(app->current);

}

void App_Draw(App* m) {

    m->current->draw(m->current);

    // Mise à jour du titre de la fenêtre
    char chaine[50] = "";
    sprintf(chaine, m->current->stateName);

    char temp[10] = "";
    sprintf(temp, " %u ms", updateChrono());
    strcat(chaine, temp);

    SDL_WM_SetCaption(chaine, NULL);
}

void setCurrentState(App* app, State* current) {

    app->precedent = app->current;
    app->current = current;

}

void App_SetDone(App* app) {

    app->done = true;
}

void gameSetup(App* app, int levelID) {

    loadLevel(&app->gameData, levelID);

}

bool App_New(App** app) {

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    App* newApp = malloc(sizeof(App));

    // create a new window
    newApp->screen = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( newApp->screen == NULL )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return false;
    }

    srand(time(NULL));

    loadGameSprites(&newApp->gameData);

    newApp->menu = Menu_Create(newApp);
    newApp->levelMenu = LevelMenu_Create(newApp);
    newApp->play = Play_Create(newApp, &newApp->gameData);
    newApp->deployment = Deployment_Create(newApp, &newApp->gameData);
    newApp->pause = Pause_Create(newApp, &newApp->gameData);

    newApp->current = (State*)&newApp->menu;

    newApp->done = false;

    *app = newApp;

    return true;
}

void App_Run(App* app) {

    while (app->done != true) {

        App_Event(app);
        App_Logic(app);
        App_Draw(app);

    }

}

State* getLevelMenuState(App* app) {

    return &app->levelMenu.state;

}

State* getMenuState(App* app) {

    return &app->menu.state;

}

State* getPlayState(App* app) {

    return &app->play.state;

}

State* getPauseState(App* app) {

    return &app->pause.state;

}

State* getDeploymentState(App* app) {

    return &app->deployment.state;

}

State* getPrecedentState(App* app) {

    return app->precedent;

}

unsigned int updateChrono() {

    static unsigned int precedent = 0;

    unsigned int duration = SDL_GetTicks() - precedent;
    precedent = SDL_GetTicks(); // On met à jour la date de la dernière image

    return duration;
}
