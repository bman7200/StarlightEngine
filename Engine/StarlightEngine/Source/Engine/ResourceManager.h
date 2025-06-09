// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// SDL
#include <SDL3/SDL_filesystem.h>

// Starlight Engine
#include "Framework/String.h"

static FString FAssetPath(const FString& RelativeAssetPath)
{
	return SDL_GetBasePath() + FString(R"(Assets\)") + RelativeAssetPath;
}

class ResourceManager
{
};

// Global Engine Instance
static ResourceManager* GResourceManager = nullptr;
