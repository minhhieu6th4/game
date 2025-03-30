#include "EnemyTank.h"
#include "game.h"
#include <algorithm>


using namespace std;

EnemyTank::EnemyTank(int startX, int startY)
{
    moveDelay = 15;
    shootDelay = 0;
    x = startX;
    y = startY;
    rect = {x,y,TILE_SIZE,TILE_SIZE};
    dirX = 0;
    dirY = 1;
    active = true;
}


void EnemyTank :: move(const vector<Wall>& walls)
{
    if (--moveDelay > 0 )
    {
        return;
    }
    moveDelay = 15;
    int r = rand() % 4;
    if ( r == 0 )
    {
        this->dirX = 0;
        this->dirY = -5;
    }
    else if ( r == 1)
    {
        this->dirX = 0;
        this->dirY = 5;
    }
    else if ( r == 2)
    {
        this->dirX = -5;
        this->dirY = 0;
    }
    else if ( r == 3)
    {
        this->dirX = 5;
        this->dirY = 0;
    }
    int newX = x + this-> dirX;
    int newY = y + this-> dirY;

    SDL_Rect newRect = {newX, newY, TILE_SIZE, TILE_SIZE};
    int length = walls.size();
    for ( int i = 0; i < length ; i++)
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

    if (dirX == 0 && dirY == -5) angle = 0.0;   // Lên
    if (dirX == 0 && dirY == 5)  angle = 180.0; // Xuống
    if (dirX == -5 && dirY == 0) angle = 270.0; // Trái
    if (dirX == 5 && dirY == 0)  angle = 90.0;  // Phải
}

void EnemyTank :: shoot()
{
    if (--shootDelay > 0 )
    {
        return;
    }
    shootDelay = 3;
    bullets.push_back(Bullet(x + TILE_SIZE / 2 - 5, y + TILE_SIZE / 2 - 5, this->dirX, this->dirY));

}

void EnemyTank::updateBullets()
{
    for ( auto &bullet : bullets)
    {
        bullet.move();
    }
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [] (Bullet &b )
    {
        return !b.active;
    }), bullets.end());
}


void  EnemyTank ::render(SDL_Renderer* renderer)
{
//    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
//    SDL_RenderFillRect(renderer, &rect);
    SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "enemyTank.png");
    SDL_RenderCopyEx(renderer, imageTexture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
    SDL_DestroyTexture(imageTexture);

    for (auto &bullet : bullets)
    {
        bullet.render(renderer);
    }
}
