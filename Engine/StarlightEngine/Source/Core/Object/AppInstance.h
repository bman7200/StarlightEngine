// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "Object.h"
#include "World.h"

class SAppInstance : SObject
{
public:
	TWeakObjectPtr<SWorld> GetWorld() { return CurrentWorld; }

	void LoadWorld(const TObjectPtr<SWorld>& NewWorld);

private:
	TObjectPtr<SWorld> CurrentWorld;
};
