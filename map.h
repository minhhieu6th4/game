#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <iostream>

class Wall
{
public:
    int x,y;
    SDL_Rect rect;
    bool active;
    Wall(int startX , int startY);
    void render(SDL_Renderer* renderer);
};

#endif // WALL_h
