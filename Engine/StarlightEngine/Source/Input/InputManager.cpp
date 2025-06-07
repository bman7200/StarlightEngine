// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "InputManager.h"

// Libraries
#include <iostream>

// Starlight Engine
#include "Debug/Logging.h"

InputManager::InputManager()
{
	// Construction goes here
}

InputManager::~InputManager()
{
	Shutdown();
}

bool InputManager::Initialize()
{
	return true;
}

void InputManager::Shutdown()
{
	// Shutdown
}

void InputManager::ProcessEvents(bool& IsRunning)
{
	SDL_Event ActiveEvent;
	while (SDL_PollEvent(&ActiveEvent))
	{
		switch (ActiveEvent.type)
		{
		case SDL_EVENT_QUIT:
			IsRunning = false;
			SL_LOG_FUNC("SDL_EVENT_QUIT received. Shutting down engine.");
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			break;
		default:
			break;
		}
	}
}
