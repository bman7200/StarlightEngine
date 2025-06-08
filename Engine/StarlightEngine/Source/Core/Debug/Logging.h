// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

#ifdef _DEBUG

#include <iostream>
#define SL_LOG(message) std::cout << "SL: " << (message) << std::endl
#define SL_LOG_FUNC(message) std::cout << "SL: " << __FUNCTION__ << " - " << (message) << std::endl

struct DebugFunctionScope
{
	DebugFunctionScope(const FString& InFunctionName)
	{
		FunctionName = InFunctionName;
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
