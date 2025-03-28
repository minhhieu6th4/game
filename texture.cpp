#include "texture.h"
#include <iostream>

Texture::Texture() {
    texture = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path) {
    free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Không thể tải ảnh " << path << "! Lỗi SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
        std::cerr << "Không thể tạo texture từ " << path << "! Lỗi SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);

    texture = newTexture;
    return true;
}

void Texture::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = { x, y, width, height };

    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int Texture::getWidth() {
    return width;
}

int Texture::getHeight() {
    return height;
}
