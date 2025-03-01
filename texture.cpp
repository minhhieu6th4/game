#include "Texture.h"
#include <iostream>

using namespace std;

Texture::Texture() : texture(nullptr), width(0), height(0) {}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, string path) {
    free(); // Xóa texture cũ nếu có

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cout << "Lỗi load ảnh: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        std::cout << "Lỗi tạo texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    return true;
}

void Texture::render(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect renderQuad = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

void Texture::free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = height = 0;
    }
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}

SDL_Texture* Texture::getTexture() {
    return texture;
}
