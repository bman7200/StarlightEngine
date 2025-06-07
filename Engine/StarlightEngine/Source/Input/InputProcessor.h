// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "CoreMinimal.h"
#include "InputKeys.h"

class InputProcessor
{
public:
	InputProcessor();
	~InputProcessor();

	virtual void HandleKeyDown(const SKey& Key) {}
};
