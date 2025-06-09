// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Engine
#include "Framework/String.h"
#include "Input/InputManager.h"
#include "Renderer/Renderer.h"

// Forward Declarations
struct SDL_Window;

class Engine
{
	friend int main(int argc, char* argv[]);

	Engine();
	~Engine();

	bool Initialise();
	void Shutdown();

	bool InitialiseMainWindow();
	void ShutdownMainWindow();

	SDL_Window* m_mainWindow = nullptr;
	Renderer m_mainRenderer;
	InputManager m_inputManager;

	void Tick(bool& IsRunning, float DeltaTime);
	void Render();

public:
	class Version
	{
	public:
		static constexpr int MAJOR = 0;
		static constexpr int MINOR = 1;
		static constexpr int PATCH = 0;

		static FString GetVersionString();
	};

	class Display
	{
	public:
		static FString GetEngineTitleString();
		static FString GetEngineTitleString_Configuration();
		static FString GetEngineTitleString_Configuration_Version();

		static FString GetConfigurationTitleString();
	};
};

// Global Engine Instance
static Engine* GEngine = nullptr;
