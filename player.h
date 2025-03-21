#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "bullet.h"
#include <vector>

using namespace std;


class PlayerTank
{
public:
    int x,y;
    int dirX, dirY;
    SDL_Rect rect;
    PlayerTank ( int startX , int startY);
    vector<Bullet> bullets;
    void move(int dx, int dy, const vector<Wall> &walls);
    void render(SDL_Renderer* renderer);
    void shoot();
    void updateBullets();

};

#endif // PLAYER_H
