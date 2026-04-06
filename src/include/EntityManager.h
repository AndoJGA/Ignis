#pragma once
#include <SDL3/SDL.h>

enum class EntityType { PLAYER, ENEMY };

struct Entity {
    float x, y;
    float vx, vy;
    float speed;
    SDL_FRect rect; // SDL3 uses floats for sub-pixel precision
    EntityType type;

    void Update(float dt);
    void Render(SDL_Renderer* renderer);
};