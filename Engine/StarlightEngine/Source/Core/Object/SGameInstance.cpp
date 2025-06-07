// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "SGameInstance.h"

void SGameInstance::LoadWorld(const TObjectPtr<SWorld>& NewWorld)
{
	CurrentWorld.reset();

	CurrentWorld = NewWorld;
}
