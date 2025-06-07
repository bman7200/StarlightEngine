// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Initialise(SDL_Window* Window);
    void Shutdown();
    
    void Clear();
    void Present();
    
    SDL_Renderer* GetSDLRenderer() const { return m_renderer; }
    
private:
    SDL_Renderer* m_renderer = nullptr;
};