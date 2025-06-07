// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "SObject.h"
#include "SWorld.h"

class SGameInstance : SObject
{
public:
	TObjectWeakPtr<SWorld> GetWorld() { return CurrentWorld; }

	void LoadWorld(const TObjectPtr<SWorld>& NewWorld);

private:
	TObjectPtr<SWorld> CurrentWorld;
};
