// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "AppInstance.h"

void SAppInstance::LoadWorld(const TObjectPtr<SWorld>& NewWorld)
{
	CurrentWorld.reset();

	CurrentWorld = NewWorld;
}
