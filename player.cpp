#include "player.h"
#include "game.h"
#include <algorithm>

using namespace std;

PlayerTank :: PlayerTank( int startX, int startY)
{
    x = startX;
    y = startY;
    rect = {x, y, TILE_SIZE, TILE_SIZE};
    dirX = 0;
    dirY = 0;
}

void PlayerTank :: move(int dx, int dy, const vector<Wall> &walls)
{
    int newX = x + dx;
    int newY = y + dy;
    this-> dirX = dx;
    this-> dirY = dy;

    SDL_Rect newRect = {newX, newY, TILE_SIZE, TILE_SIZE};
    int len = walls.size();
    for ( int i = 0; i < len ; i++)
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
    if (dx == 0 && dy == -5) angle = 0.0;   // Lên
    if (dx  == 0 && dy  == 5)  angle = 180.0; // Xuống
    if (dx  == -5 && dy  == 0) angle = 270.0; // Trái
    if (dx  == 5 && dy  == 0)  angle = 90.0;  // Phải

}

void PlayerTank::shoot()
{
    Uint32 currentTime = SDL_GetTicks(); // Lấy thời gian hiện tại

    if (currentTime - lastShotTime < shotCooldown)
        return; // Nếu chưa đủ thời gian chờ, không bắn

    lastShotTime = currentTime; // Cập nhật thời gian bắn mới

    // Nếu chưa di chuyển, đặt hướng mặc định (bắn lên)
//    int bulletDirX = (dirX == 0 && dirY == 0) ? 0 : dirX;
//    int bulletDirY = (dirX == 0 && dirY == 0) ? -5 : dirY;
    int speedMultiplier = 2; // Tăng tốc độ đạn lên gấp đôi
    int bulletDirX = (dirX == 0 && dirY == 0) ? 0 : dirX * speedMultiplier;
    int bulletDirY = (dirX == 0 && dirY == 0) ? -5 * speedMultiplier : dirY * speedMultiplier;

    bullets.push_back(Bullet(x + TILE_SIZE / 2 - 5, y + TILE_SIZE / 2 - 5, bulletDirX, bulletDirY));



}


void PlayerTank ::updateBullets()
{
    for ( auto &bullet : bullets)
    {
        bullet.move();
    }
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
                            [](Bullet &b)
    {
        return !b.active;
    }), bullets.end());
}


void PlayerTank ::render(SDL_Renderer *renderer)
{
//     SDL_SetRenderDrawColor(renderer,255,255,0,255);
//     SDL_RenderFillRect(renderer, &rect);
    SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "upplayer.png");
    SDL_RenderCopyEx(renderer, imageTexture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
    for (auto &bullet : bullets)
    {
        bullet.render(renderer);
    }
    SDL_DestroyTexture(imageTexture);
}

