#include "vehicle.h"

Vehicle::Vehicle(int x, int y, int speed) : x(x), y(y), speed(speed) {}

void Vehicle::update() {
    x += speed;
    if (x > 800) x = -50;
}

void Vehicle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect vehicleRect = { x, y, 60, 40 };
    SDL_RenderFillRect(renderer, &vehicleRect);
}
