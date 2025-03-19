#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

using namespace std;

class Game;

class Wall;

class PlayerTank
{
public:
    int x,y;
    int dirX, dirY;
    SDL_Rect rect;
    PlayerTank ( int startX , int startY);
    void move(int dx, int dy, const vector<Wall> &walls);
    void render(SDL_Renderer* renderer);
};

#endif // PLAYER_H
