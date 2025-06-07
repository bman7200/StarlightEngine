// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "InputManager.h"

// Libraries
#include <iostream>

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
			std::cout << "InputManager: Quit event received. Shutting down." << '\n';
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			
			break;
		default:
			break;
		}
	}
}