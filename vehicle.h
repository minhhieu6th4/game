#ifndef VEHICLE_H
#define VEHICLE_H

#include <SDL.h>

class Vehicle {
public:
    Vehicle(int x, int y, int speed);
    void update();
    void render(SDL_Renderer* renderer);

    int getX() { return x; }
    int getY() { return y; }

private:
    int x, y;
    int speed;
};

#endif
