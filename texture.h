#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* renderer, std::string path);
    void render(SDL_Renderer* renderer, int x, int y, int w = 100, int h = 120);
    void free();

    int getWidth();
    int getHeight();
    SDL_Texture* getTexture();

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif
