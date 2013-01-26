#ifndef _STATE_GUARD
#define _STATE_GUARD

#include "SDL_events.h"
#include "SDL_video.h"

typedef struct App App;

typedef struct State {

    App* appRef;

    void (*event)(struct State*, SDL_Event);
    void (*logic)(struct State*);
    void (*draw)(struct State*);

    SDL_Surface* screen;
    char stateName[50];

} State;

State createState(App* appRef, void (*event)(State*, SDL_Event), void (*logic)(State*), void (*draw)(State*), char* stateName);

#endif // STATE

