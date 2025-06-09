// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// SDL
#include <SDL3/SDL.h>

// Starlight Engine
#include "Pointers.h"
#include "Framework/Color.h"

// Forward Declarations
class Engine;

class Renderer
{
	friend Engine;

	// =============================================
	// DE/CONSTRUCTORS
	// =============================================

	Renderer();
	~Renderer();

	// =============================================
	// RENDERER MANAGEMENT
	// =============================================
protected:
	bool Initialise(SDL_Window* Window);
	void Shutdown();

	void BeginFrame() const;
	void EndFrame() const;

	// =============================================
	// RENDERING
	// =============================================
public:
	// Clears using the current ClearColor.
	// Use `SetClearColor` to change the current ClearColor.
	// Use `ClearCustom` for custom one-time use.
	void Clear() const;

	// Clears using a custom color (does not change cached ClearColor).
	void ClearCustom(FRenderColor InClearColor) const;

	// Presents the final render
	void Present() const;

	void SetClearColor(const FRenderColor& NewValue);
	const FRenderColor& GetClearColor() const;

	void DrawRectangle(float X, float Y, float W, float H) const;
	void DrawRectangle(const SDL_FRect* Rect) const;

protected:
	FRenderColor m_clearColor = ERenderColors::Black;

	// =============================================
	// SDL
	// =============================================
private:
	SDL_Renderer* GetSDLRenderer() const { return m_renderer; }
	SDL_Renderer* m_renderer = nullptr;
};
