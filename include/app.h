#ifndef _APP_GUARD
#define _APP_GUARD

#include <stdbool.h>

typedef struct App App;
typedef struct State State;

State* getLevelMenuState(App* app);
State* getPlayState(App* app);
State* getPauseState(App* app);
State* getDeploymentState(App* app);
State* getMenuState(App* app);
State* getPrecedentState(App* app);
void setCurrentState(App* app, State* current);
void App_SetDone(App* app);
void gameSetup(App* app, int levelID);
bool App_New(App** app);
void App_Run(App* app);

#endif // MANAGER

