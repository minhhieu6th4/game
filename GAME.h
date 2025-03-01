#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Card.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Card*> cards;

    Card* firstCard;
    Card* secondCard;

    void loadCards();
    void handleEvents();
    void update();
    void render();
};

#endif
