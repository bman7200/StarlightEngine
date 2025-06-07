// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL_video.h>

// Engine
#include "../Input/InputManager.h"
#include "../Renderer/Renderer.h"

class Engine
{
public:
	Engine();
	~Engine();
	
	bool Initialise();
	void Shutdown();

private:
	bool InitialiseMainWindow();
	void ShutdownMainWindow();

	SDL_Window* m_mainWindow;
	Renderer m_mainRenderer;
	InputManager m_inputManager;

public:
	void Tick(bool& IsRunning, float DeltaTime);
	void Render();
};
