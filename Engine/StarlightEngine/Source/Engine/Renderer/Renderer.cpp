// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Renderer.h"

// Libraries
#include <iostream>

// Starlight Engine
#include <SDL3_image/SDL_image.h>

#include "Debug/Logging.h"
#include "Engine/ResourceManager.h"

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
		SL_LOG_FUNC(LogRenderer, Error, "Renderer: Initialise failed because Window is invalid!");
	}

	m_renderer = SDL_CreateRenderer(Window, nullptr);
	if (m_renderer == nullptr)
	{
		SL_LOG_FUNC(LogRenderer, Error, "Renderer: SDL_CreateRenderer failed! SDL_Error: " + SDL_GetErrorFString());
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

void Renderer::BeginFrame() const
{
	if (m_renderer == nullptr)
	{
		return;
	}

	Clear();
}

void Renderer::EndFrame() const
{
	if (m_renderer == nullptr)
	{
		return;
	}

	SDL_Surface* MainIconSurface = IMG_Load(FAssetPath(R"(Editor\StarlightEngine\Icon160px.png)"));
	SDL_Texture* MainIconTexture = SDL_CreateTextureFromSurface(m_renderer, MainIconSurface);
	// SDL_SetTextureScaleMode(MainIconTexture, SDL_SCALEMODE_NEAREST);
	const SDL_FRect FRect = {0, 0, static_cast<float>(MainIconTexture->w), static_cast<float>(MainIconTexture->h)};
	SDL_RenderTexture(m_renderer, MainIconTexture, nullptr, nullptr);
	SDL_DestroyTexture(MainIconTexture);
	SDL_DestroySurface(MainIconSurface);

	Present();
}

void Renderer::Clear() const
{
	ClearCustom(m_clearColor);
}

void Renderer::ClearCustom(FRenderColor InClearColor) const
{
	SDL_SetRenderDrawColorFloat(m_renderer, InClearColor.R, InClearColor.G, InClearColor.B, InClearColor.A);
	SDL_RenderClear(m_renderer);
}

void Renderer::Present() const
{
	if (m_renderer == nullptr)
	{
		return;
	}

	SDL_RenderPresent(m_renderer);
}

void Renderer::SetClearColor(const FRenderColor& NewValue)
{
	m_clearColor = NewValue;
}

const FRenderColor& Renderer::GetClearColor() const
{
	return m_clearColor;
}

void Renderer::DrawRectangle(float X, float Y, float W, float H) const
{
	SDL_FRect FRect({X, Y, W, H});
	DrawRectangle(&FRect);
}

void Renderer::DrawRectangle(const SDL_FRect* Rect) const
{
	SDL_RenderFillRect(m_renderer, Rect);
}
