#ifndef WALL_H
#define WALL_H

#include <iostream>
#include <SDL.h>
#include <vector>

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
