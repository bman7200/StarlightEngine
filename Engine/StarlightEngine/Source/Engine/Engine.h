// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <string>
#include <SDL3/SDL_video.h>

// Engine
#include "Input/InputManager.h"
#include "Renderer/Renderer.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialise();
	void Shutdown();

private:
	bool InitialiseMainWindow();
	void ShutdownMainWindow();

	SDL_Window* m_mainWindow;
	Renderer m_mainRenderer;
	InputManager m_inputManager;

public:
	void Tick(bool& IsRunning, float DeltaTime);
	void Render();

	class Version
	{
	public:
		static constexpr int MAJOR = 1;
		static constexpr int MINOR = 0;
		static constexpr int PATCH = 0;

		static std::string GetVersionString();
	};

	class Display
	{
	public:
		static std::string GetEngineTitleString();
		static std::string GetEngineTitleString_Configuration();
		static std::string GetEngineTitleString_Configuration_Version();

		static std::string GetConfigurationTitleString();
	};
};

// Global Engine Instance
static Engine* GEngine = nullptr;
