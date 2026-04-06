#include "include/Engine.h"
#include <iostream>

bool Engine::Initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    m_window = SDL_CreateWindow("Ignis Engine", 1280, 720, 0);
    m_renderer = SDL_CreateRenderer(m_window, NULL); // SDL3 auto-selects best backend

    if (!m_window || !m_renderer) return false;

    // Create 1 Player and 100 Enemies for the "Stress Test"
    m_entities.push_back({100, 100, 0, 0, 300.0f, {0,0,32,32}, EntityType::PLAYER});

    for(int i=0; i<100; i++) {
        m_entities.push_back({(float)(rand()%1200), (float)(rand()%700), 1, 1, 100.0f, {0,0,24,24}, EntityType::ENEMY});
    }

    m_isRunning = true;
    return true;
}

void Engine::Update(float dt) {
    for (auto& e : m_entities) {
        e.x += e.vx * e.speed * dt;
        e.y += e.vy * e.speed * dt;

        // Simple Screen Bounce Logic
        if (e.x < 0 || e.x > 1280) e.vx *= -1;
        if (e.y < 0 || e.y > 720) e.vy *= -1;

        e.rect.x = e.x;
        e.rect.y = e.y;
    }
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_renderer, 10, 10, 15, 255); // Dark Slate Background
    SDL_RenderClear(m_renderer);

    for (auto& e : m_entities) {
        if (e.type == EntityType::PLAYER)
            SDL_SetRenderDrawColor(m_renderer, 0, 200, 255, 255); // Blue Player
        else
            SDL_SetRenderDrawColor(m_renderer, 255, 50, 50, 255); // Red Enemy

        SDL_RenderFillRect(m_renderer, &e.rect);
    }

    SDL_RenderPresent(m_renderer);
}

void Engine::Run() {
    Uint64 lastTime = SDL_GetTicksNS(); // SDL3 High-res clock

    while (m_isRunning) {
        Uint64 currentTime = SDL_GetTicksNS();
        // Calculate the time difference in seconds
        float deltaTime = (float)(currentTime - lastTime) / 1000000000.0f;
        lastTime = currentTime;

        // 1. Process Input
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) m_isRunning = false;
        }

        // 2. Logic Update
        Update(deltaTime);

        // 3. Graphics Render
        Render();
    }
}

void Engine::Shutdown() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}