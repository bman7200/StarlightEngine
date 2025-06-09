// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Renderer.h"

// Libraries
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
		std::cerr << "Renderer: Initialise failed because Window is invalid!" << std::endl;
	}

	m_renderer = SDL_CreateRenderer(Window, nullptr);
	if (m_renderer == nullptr)
	{
		std::cerr << "Renderer: SDL_CreateRenderer failed! SDL_Error: " << SDL_GetError() << std::endl;
		// BHH TODO: Throw an exception
	}

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
	if (m_renderer == nullptr)
	{
		return;
	}

	SDL_SetRenderDrawColorFloat(m_renderer, ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
	SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
	if (m_renderer == nullptr)
	{
		return;
	}

	SDL_Window* Window = SDL_GetRenderWindow(m_renderer);

	SDL_FRect Rect = {0, 0, 150, 100};

	int WindowW, WindowH;
	SDL_GetWindowSize(Window, &WindowW, &WindowH);

	Rect.x += static_cast<float>(WindowW) / 2.0f - Rect.w / 2.0f;
	Rect.y += static_cast<float>(WindowH) / 2.0f - Rect.h / 2.0f;

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_renderer, &Rect);

	SDL_RenderPresent(m_renderer);
}

void Renderer::SetClearColor(const FRenderColor& NewValue)
{
	ClearColor = NewValue;
}

FRenderColor Renderer::GetClearColor() const
{
	return ClearColor;
}
