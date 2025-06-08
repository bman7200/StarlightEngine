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

	virtual void HandleKeyDown(const FInputKey& InputKey) {}
	virtual void HandleKeyUp(const FInputKey& InputKey) {}
};
