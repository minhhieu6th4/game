#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player(int x, int y);

    void handleInput(SDL_Event& event);
    void render(SDL_Renderer* renderer);

    int getX() { return x; }
    int getY() { return y; }

private:
    int x, y;
    int speed;
};

#endif
