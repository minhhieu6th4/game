#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* renderer, const std::string& path);
    void free();
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif
