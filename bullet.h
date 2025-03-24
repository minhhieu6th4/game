#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Bullet
{
public:
    int x,y;
    int dx,dy;
    SDL_Rect rect;
    bool active;
    Bullet(int StartX , int StartY , int dirX , int dirY);
    void move();
    void render(SDL_Renderer *renderer);
};

#endif // BULLET_H
