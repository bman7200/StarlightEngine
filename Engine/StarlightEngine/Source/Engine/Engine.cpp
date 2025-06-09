// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Engine.h"

// Libraries
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// Starlight Engine
#include "ResourceManager.h"
#include "Debug/Logging.h"
#include "Input/InputManager.h"
#include "Renderer/Renderer.h"

Engine::Engine()
{
	if (GEngine == nullptr)
	{
		GEngine = this;
	}
	else
	{
		SL_LOG(LogEngine, Error, "Additional Engine was created when GEngine was already valid.");
		delete this;
	}
}

Engine::~Engine()
{
	Shutdown();
}

bool Engine::Initialise()
{
	SL_LOG_FUNC_SCOPE(LogEngine, Debug);

	if (InitialiseMainWindow() == false)
	{
		return false;
	}

	if (m_inputManager.Initialize() == false)
	{
		return false;
	}

	return true;
}

void Engine::Shutdown()
{
	SL_LOG_FUNC_SCOPE(LogEngine, Debug);

	ShutdownMainWindow();
}

bool Engine::InitialiseMainWindow()
{
	SL_LOG_FUNC_SCOPE(LogEngine, Debug);

	const SDL_PropertiesID MainWindowProperties = SDL_CreateProperties();
	#if WITH_EDITOR
	SDL_SetStringProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_TITLE_STRING, Display::GetEngineTitleString_Configuration_Version());
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 800);
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 600);

	Sint64 MainWindowFlags = SDL_WINDOW_RESIZABLE;
	// BHH TODO: Cache maximized based on last use of engine.
	// MainWindowFlags |= SDL_WINDOW_MAXIMIZED;
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_FLAGS_NUMBER, MainWindowFlags);
	#else
	SDL_SetStringProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Game Project Name");
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 800);
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 600);
	#endif

	m_mainWindow = SDL_CreateWindowWithProperties(MainWindowProperties);
	SDL_DestroyProperties(MainWindowProperties);

	if (m_mainWindow == nullptr)
	{
		// BHH TODO: Throw an exception.
		SL_LOG_FUNC(LogEngine, Error, "MainWindow could not be Created! SDL_Error: " + SDL_GetErrorFString());
		return false;
	}

	#if WITH_EDITOR
	// Resize based on screen
	{
		SDL_DisplayID MainWindowDisplayID = SDL_GetDisplayForWindow(m_mainWindow);
		SDL_Rect DisplayUsableBounds;
		if (SDL_GetDisplayUsableBounds(MainWindowDisplayID, &DisplayUsableBounds))
		{
			DisplayUsableBounds.x += static_cast<int>(static_cast<float>(DisplayUsableBounds.w) * 0.1f);
			DisplayUsableBounds.y += static_cast<int>(static_cast<float>(DisplayUsableBounds.h) * 0.1f);
			DisplayUsableBounds.w = static_cast<int>(static_cast<float>(DisplayUsableBounds.w) * 0.8f);
			DisplayUsableBounds.h = static_cast<int>(static_cast<float>(DisplayUsableBounds.h) * 0.8f);

			SDL_SetWindowPosition(m_mainWindow, DisplayUsableBounds.x, DisplayUsableBounds.y);
			SDL_SetWindowSize(m_mainWindow, DisplayUsableBounds.w, DisplayUsableBounds.h);
		}
	}
	#endif

	// Renderer
	m_mainRenderer.Initialise(m_mainWindow);

	return true;
}

void Engine::ShutdownMainWindow()
{
	SL_LOG_FUNC_SCOPE(LogEngine, Debug);

	m_mainRenderer.Shutdown();
	SDL_DestroyWindow(m_mainWindow);
}

void Engine::Tick(bool& IsRunning, float DeltaTime)
{
	m_inputManager.ProcessEvents(IsRunning);
	if (IsRunning == false)
	{
		return;
	}

	Render();
}

void Engine::Render()
{
	m_mainRenderer.BeginFrame();

	// TODO: Render everything. Probably make the game pass separate from the UI pass.

	m_mainRenderer.EndFrame();
}

FString Engine::Version::GetVersionString()
{
	return FString(MAJOR) + "." + FString(MINOR) + "." + FString(PATCH);
}

FString Engine::Display::GetEngineTitleString()
{
	return "Starlight Engine";
}

FString Engine::Display::GetEngineTitleString_Configuration()
{
	return GetEngineTitleString() + " [" + GetConfigurationTitleString() + "]";
}

FString Engine::Display::GetEngineTitleString_Configuration_Version()
{
	return GetEngineTitleString_Configuration() + " ✦ V" + Version::GetVersionString();
}

FString Engine::Display::GetConfigurationTitleString()
{
	#if WITH_EDITOR
	#ifdef _DEBUG
	return "Debug Editor";
	#else
	return "Release Editor";
	#endif
	#else
	#ifdef _DEBUG
	return "Debug Game";
	#else
	return "Release Game";
	#endif
	#endif
}
