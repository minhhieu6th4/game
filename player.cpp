#include "player.h"
#include "game.h"

using namespace std;

PlayerTank :: PlayerTank( int startX , int startY)
 {
 	x = startX;
 	y = startY;
 	rect = {x, y, TILE_SIZE, TILE_SIZE};
 	dirX = 0;
 	dirY = 0;
 }

 void PlayerTank :: render (SDL_Renderer* renderer)
 {
 	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
 	SDL_RenderFillRect(renderer, &rect);
 }

 void PlayerTank :: move(int dx, int dy, const vector<Wall> &walls)
 {
 	int newX = x + dx;
 	int newY = y + dy;
 	this-> dirX = dx;
 	this-> dirY = dy;

 	SDL_Rect newRect = {newX , newY , TILE_SIZE , TILE_SIZE};
 	for ( int i = 0; i < walls.size() ; i++)
 	{
 		if (walls[i].active && SDL_HasIntersection(&newRect, &walls[i].rect))
 		{
 			return;
 		}
 	}

 	if ( newX >= TILE_SIZE && newX <= SCREEN_WIDTH - TILE_SIZE * 2 &&
 		 newY >= TILE_SIZE && newY <= SCREEN_HEIGHT - TILE_SIZE * 2)
 	{
 		x = newX;
 		y = newY;
 		rect.x = x;
 		rect.y = y;
 	}
 }
