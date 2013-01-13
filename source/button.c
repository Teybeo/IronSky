#include "button.h"

void updateButtonState(Button *button, Point posMouse)
{
    if (posMouse.x > button->rect.x && posMouse.x < button->rect.x + button->rect.w && posMouse.y < button->rect.y + button->rect.h && posMouse.y > button->rect.y)
    {
        button->state = HOVER;
    }
    else
        button->state = NORMAL;
}

void drawButton(Button b, SDL_Surface* screen) {

    SDL_FillRect(screen, &b.rect, b.color[b.state]);

}
