#ifndef CARD_H
#define CARD_H

#include <SDL.h>

class Card {
public:
    Card(int x, int y, SDL_Texture* front, SDL_Texture* back);

    void render(SDL_Renderer* renderer);
    bool isClicked(int mouseX, int mouseY);
    void flip();
    bool isFlipped();
    bool isMatched();
    void setMatched();

    SDL_Texture* getFrontTexture();

private:
    int x, y;
    bool flipped;
    bool matched;
    SDL_Texture* frontTexture;
    SDL_Texture* backTexture;
};

#endif
