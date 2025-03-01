#include "player.h"

Player::Player(int x, int y) : x(x), y(y), speed(50) {}

void Player::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:    y -= speed; break;
            case SDLK_DOWN:  y += speed; break;
            case SDLK_LEFT:  x -= speed; break;
            case SDLK_RIGHT: x += speed; break;
        }
    }
}

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect playerRect = { x, y, 50, 50 };
    SDL_RenderFillRect(renderer, &playerRect);
}
