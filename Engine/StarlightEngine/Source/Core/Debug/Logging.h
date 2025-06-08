// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

#ifdef _DEBUG

// Libraries
#include <iostream>
#include <utility>

// Starlight Engine
#include "Framework/String.h"

// Log message
#define SL_LOG(message) std::cout << "SL: " << (message) << std::endl

// Log message with function name
#define SL_LOG_FUNC(message) SL_LOG(FString(__FUNCTION__) + " - " + (message))

struct DebugFunctionScope
{
	DebugFunctionScope(FString InFunctionName)
	{
		FunctionName = std::move(InFunctionName);
		SL_LOG(FunctionName + FString(" Started"));
	}

	~DebugFunctionScope()
	{
		SL_LOG(FunctionName + FString(" Ended"));
	}

private:
	FString FunctionName;
};
#define SL_LOG_FUNC_SCOPE DebugFunctionScope DebugFunctionScope_##__FUNCTION__ = DebugFunctionScope(__FUNCTION__)

#else

// logs are compiled out
#define SL_LOG
#define SL_LOG_FUNC
#define SL_LOG_FUNC_SCOPE

#endif
