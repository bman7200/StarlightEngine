// Copyright © 2025 Bman, Inc. All rights reserved.

// Libraries
#include <SDL3/SDL.h>
#include <iostream>

// Headers
#include "Engine/Engine.h"

int main(int argc, char* argv[])
{
    // Initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    // Initialise Engine
    Engine* MainEngine = new Engine();
    if (MainEngine->Initialise() == false)
    {
        delete MainEngine;
        SDL_Quit();
        return 0;
    }
    
    // Main game loop
    Uint64 LastTick = SDL_GetPerformanceCounter();
    bool IsRunning = true;
    while (IsRunning)
    {
        Uint64 FrameStartTime = SDL_GetTicks();
        
        Uint64 CurrentTick = SDL_GetPerformanceCounter();
        float DeltaTime = (float)(CurrentTick - LastTick) / (float)SDL_GetPerformanceFrequency();
        LastTick = CurrentTick;
        
        MainEngine->Tick(IsRunning, DeltaTime);

        if (IsRunning == false)
        {
            break;
        }
        
        // Frame pacing
        constexpr int MAX_FPS = 60;
        constexpr int FRAME_DELAY_MS = 1000 / MAX_FPS;
        Uint64 FrameEndTime = SDL_GetTicks();
        Uint64 FrameDuration = FrameEndTime - FrameStartTime;
        if (FrameDuration < FRAME_DELAY_MS)
        {
            SDL_Delay(FRAME_DELAY_MS - FrameDuration);  // NOLINT(clang-diagnostic-shorten-64-to-32)
        }
    }

    // Clean up
    MainEngine->Shutdown();
    delete MainEngine;
    MainEngine = nullptr;

    // Shutdown
    SDL_Quit();
    return 0;
}