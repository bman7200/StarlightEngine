// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Engine.h"

// Libraries
#include <iostream>
#include <ostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <string>

// Starlight
#include "Input/InputManager.h"
#include "Renderer/Renderer.h"

#define LOG_ENGINE_START_FUNCTION std::cout << "Engine: Starting " << __FUNCTION__ << '\n'
#define LOG_ENGINE_COMPLETE_FUNCTION std::cout << "Engine: Completed " << __FUNCTION__ << '\n'

Engine::Engine() :
	m_mainWindow(nullptr)
{
	// Do nothing for now
}

Engine::~Engine()
{
	Shutdown();
}

bool Engine::Initialise()
{
	LOG_ENGINE_START_FUNCTION;

	if (InitialiseMainWindow() == false)
	{
		return false;
	}

	if (m_inputManager.Initialize() == false)
	{
		return false;
	}

	LOG_ENGINE_COMPLETE_FUNCTION;
	return true;
}

void Engine::Shutdown()
{
	LOG_ENGINE_START_FUNCTION;

	ShutdownMainWindow();

	LOG_ENGINE_COMPLETE_FUNCTION;
}

bool Engine::InitialiseMainWindow()
{
	LOG_ENGINE_START_FUNCTION;

	const SDL_PropertiesID MainWindowProperties = SDL_CreateProperties();
#if WITH_EDITOR
	SDL_SetStringProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_TITLE_STRING, Display::GetEngineTitleString_Configuration_Version().c_str());
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 800);
	SDL_SetNumberProperty(MainWindowProperties, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 600);

	constexpr Sint64 MainWindowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
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
		// std::cout << "MainWindow could not be created! SDL_Error: " << SDL_GetError() << '\n';
		return false;
	}

	// Renderer
	m_mainRenderer.Initialise(m_mainWindow);

	LOG_ENGINE_COMPLETE_FUNCTION;
	return true;
}

void Engine::ShutdownMainWindow()
{
	LOG_ENGINE_START_FUNCTION;

	m_mainRenderer.Shutdown();
	SDL_DestroyWindow(m_mainWindow);

	LOG_ENGINE_COMPLETE_FUNCTION;
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
	SDL_Renderer* Renderer = m_mainRenderer.GetSDLRenderer();

	SDL_RenderClear(Renderer);

	// TODO: Render everything. Probably make the game pass separate from the UI pass.

	SDL_RenderPresent(Renderer);
}

std::string Engine::Version::GetVersionString()
{
	return std::to_string(MAJOR) + "." + std::to_string(MINOR) + "." + std::to_string(PATCH);
}

std::string Engine::Display::GetEngineTitleString()
{
	return "Starlight Engine";
}

std::string Engine::Display::GetConfigurationTitleString()
{
#if WITH_EDITOR
#if _DEBUG
	return "Debug Editor";
#else
	return "Release Editor";
#endif
#else
#if _DEBUG
	return "Debug Game";
#else
	return "Release Game";
#endif
#endif
}

std::string Engine::Display::GetEngineTitleString_Configuration()
{
	return GetEngineTitleString() + " [" + GetConfigurationTitleString() + "]";
}

std::string Engine::Display::GetEngineTitleString_Configuration_Version()
{
	return GetEngineTitleString_Configuration() + " ✦ V" + Version::GetVersionString();
}
