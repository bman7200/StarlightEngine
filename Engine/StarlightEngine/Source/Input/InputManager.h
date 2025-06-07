// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL.h>

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	bool Initialize();
	void Shutdown();
	
	void ProcessEvents(bool& IsRunning);

	// TODO: Add methods for querying key states, mouse position, etc.
	// e.g., bool IsKeyPressed(SDL_Scancode key);
	// e.g., int GetMouseX(), GetMouseY();

private:
	// No specific members needed for basic event polling, but could store
	// key states, mouse states, etc., for more complex input handling.
};
