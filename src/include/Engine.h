#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "EntityManager.h"

class Engine {
public:
    bool Initialize();
    void Run();
    void Shutdown();

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_isRunning = false;

    std::vector<Entity> m_entities; // Our "Army" of objects

    void HandleEvents();
    void Update(float dt);
    void Render();
};