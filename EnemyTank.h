#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "game.h"
#include "bullet.h"

using namespace std;

class EnemyTank
{
public:
    int x,y;
    int dirX,dirY;
    int moveDelay, shootDelay;
    SDL_Rect rect;
    bool active;
    vector<Bullet> bullets;
    EnemyTank (int startX , int startY);
    void move(const vector<Wall>& walls);
    void shoot();
    void updateBullets();
    void render(SDL_Renderer* renderer);
};

#endif // ENEMYTANK_H
