// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Renderer.h"

#include <iostream>

Renderer::Renderer() :
	m_renderer(nullptr)
{
	//
}

Renderer::~Renderer()
{
	Shutdown();
}

bool Renderer::Initialise(SDL_Window* Window)
{
	if (Window == nullptr)
	{
		std::cerr << "Renderer: Initialise failed because Window is invalid!" << '\n';
	}

	m_renderer = SDL_CreateRenderer(Window, nullptr);
	if (m_renderer == nullptr)
	{
		std::cerr << "Renderer: SDL_CreateRenderer failed! SDL_Error: " << SDL_GetError() << '\n';
		// BHH TODO: Throw an exception
	}
	
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	return true;
}

void Renderer::Shutdown()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void Renderer::Clear()
{
	if (m_renderer != nullptr)
	{
		SDL_RenderClear(m_renderer);
	}
}

void Renderer::Present()
{
	if (m_renderer != nullptr)
	{
		SDL_RenderPresent(m_renderer);
	}
}