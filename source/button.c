#include "button.h"

void Button_UpdateState(Button *button, int mouseX, int mouseY)
{
    if (isInBox(button->rect, mouseX, mouseY))
        button->state = HOVER;
    else
        button->state = NORMAL;
}

bool isInBox(SDL_Rect rect, int x, int y) {

    return (x > rect.x && x < rect.x + rect.w && y < rect.y + rect.h && y > rect.y);

}

void Button_Draw(Button b, SDL_Surface* screen) {

    SDL_FillRect(screen, &b.rect, b.color[b.state]);

}

Button Button_Create(int x, int y, int w, int h, Uint32 colorNormal, Uint32 colorHover) {

    Button b = {};

    b.rect.x = x;
    b.rect.y = y;
    b.rect.w = w;
    b.rect.h = h;
    b.color[NORMAL] = colorNormal;
    b.color[HOVER] = colorHover;
    b.state = NORMAL;

    return b;
}
