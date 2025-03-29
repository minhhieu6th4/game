#include "map.h"
#include "game.h"

using namespace std;

Wall :: Wall( int startX, int startY)
{
    x = startX;
    y = startY;
    active = true;
    rect = { x, y, TILE_SIZE, TILE_SIZE };
}

void Wall :: render(SDL_Renderer* renderer)
{
    if(active)
    {
//        SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255);
//        SDL_RenderFillRect(renderer, &rect);
        SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "wall.png");
        SDL_RenderCopy(renderer, imageTexture, nullptr, &rect);
        SDL_DestroyTexture(imageTexture);
    }
}


