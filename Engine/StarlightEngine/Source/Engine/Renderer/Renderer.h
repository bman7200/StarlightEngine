// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL.h>

#include "Framework/Color.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialise(SDL_Window* Window);
	void Shutdown();

	void Clear();
	void Present();

	void SetClearColor(const FRenderColor& NewValue);
	FRenderColor GetClearColor() const;

	SDL_Renderer* GetSDLRenderer() const { return m_renderer; }

protected:
	SDL_Renderer* m_renderer = nullptr;

	FRenderColor ClearColor = FRenderColor(0.f);
};
