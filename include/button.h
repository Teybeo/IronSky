#ifndef _BUTTON_GUARD
#define _BUTTON_GUARD

#include "stdbool.h"
#include "SDL.h"
#include "point.h"

typedef enum {
    NORMAL,
    HOVER,
    DISABLED
} ButtonState;

typedef struct Button {

    SDL_Rect rect;     // rectangle définissant le bouton
    Uint32 color[2];   // couleur pour chaque état
    ButtonState state; // état du bouton

} Button;

void updateButtonState(Button *button, Point posMouse);
void drawButton(Button b, SDL_Surface* screen);

#endif // BUTTON

