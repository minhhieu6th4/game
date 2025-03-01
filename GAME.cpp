#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game() : window(nullptr), renderer(nullptr), firstCard(nullptr), secondCard(nullptr) {}

Game::~Game() {
    close();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("Memory Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    loadCards();
    return true;
}

void Game::loadCards() {
    SDL_Surface* backSurface = IMG_Load("bg2.png");
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    SDL_FreeSurface(backSurface);

    for (int i = 0; i < 6; ++i) {
        SDL_Surface* frontSurface = IMG_Load(("card" + std::to_string(i) + ".png").c_str());
        SDL_Texture* frontTexture = SDL_CreateTextureFromSurface(renderer, frontSurface);
        SDL_FreeSurface(frontSurface);

        cards.push_back(new Card(100 * (i % 3) + 50, 100 * (i / 3) + 50, frontTexture, backTexture));
        cards.push_back(new Card(100 * (i % 3) + 200, 100 * (i / 3) + 50, frontTexture, backTexture));
    }

    std::random_shuffle(cards.begin(), cards.end());
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return;

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x = e.button.x, y = e.button.y;

            for (auto& card : cards) {
                if (!card->isFlipped() && card->isClicked(x, y)) {
                    card->flip();
                    if (!firstCard) {
                        firstCard = card;
                    } else if (!secondCard) {
                        secondCard = card;
                    }
                    break;
                }
            }
        }
    }
}

void Game::update() {
    if (firstCard && secondCard) {
        SDL_Delay(500);
        if (firstCard->getFrontTexture() == secondCard->getFrontTexture()) {
            firstCard->setMatched();
            secondCard->setMatched();
        } else {
            firstCard->flip();
            secondCard->flip();
        }
        firstCard = nullptr;
        secondCard = nullptr;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (auto& card : cards) {
        card->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::run() {
    bool running = true;
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

void Game::close() {
    for (auto& card : cards) delete card;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
