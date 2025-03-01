#include "Card.h"

Card::Card(int x, int y, SDL_Texture* front, SDL_Texture* back)
    : x(x), y(y), flipped(false), matched(false), frontTexture(front), backTexture(back) {}

void Card::render(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, 100, 120}; // Kích thước thẻ
    SDL_RenderCopy(renderer, flipped ? frontTexture : backTexture, NULL, &rect);
}

bool Card::isClicked(int mouseX, int mouseY) {
    return mouseX > x && mouseX < x + 100 && mouseY > y && mouseY < y + 120;
}

void Card::flip() {
    flipped = !flipped;
}

bool Card::isFlipped() {
    return flipped;
}

bool Card::isMatched() {
    return matched;
}

void Card::setMatched() {
    matched = true;
}

SDL_Texture* Card::getFrontTexture() {
    return frontTexture;
}
