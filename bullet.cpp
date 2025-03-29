#include "bullet.h"
#include "game.h"

using namespace std;

Bullet :: Bullet( int StartX , int StartY , int dirX , int dirY)
{
    x = StartX;
    y = StartY;
    dx = dirX;
    dy = dirY;
    active = true;
    rect = {x,y,10,10};
}

void Bullet :: move()
{
    x += dx;
    y += dy;
    rect.x = x;
    rect.y = y;
    if ( x < TILE_SIZE || x > SCREEN_WIDTH - TILE_SIZE || y < TILE_SIZE || y > SCREEN_HEIGHT - TILE_SIZE)
    {
        active = false;
    }
}

void Bullet :: render (SDL_Renderer *renderer)
{
    if (active)
    {
//        SDL_SetRenderDrawColor(renderer,255,255,255,255);
//        SDL_RenderFillRect(renderer,&rect);
        SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "bullet.png");
        SDL_RenderCopy(renderer, imageTexture, nullptr, &rect);
        SDL_DestroyTexture(imageTexture);
    }
}


