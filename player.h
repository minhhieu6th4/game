#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"
#include "bullet.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;


class PlayerTank
{
public:
    int x,y;
    int dirX, dirY;
    SDL_Rect rect;
    vector<Bullet> bullets;
    PlayerTank ( int startX, int startY);
    void move(int dx, int dy, const vector<Wall> &walls);
    void render(SDL_Renderer* renderer);
    void shoot();
    void updateBullets();
    double angle = 0.0;
private:
    Uint32 lastShotTime = 0; // Lưu thời gian lần bắn trước
    const Uint32 shotCooldown = 500; // Thời gian chờ giữa 2 lần bắn (ms)

};

#endif // PLAYER_H
