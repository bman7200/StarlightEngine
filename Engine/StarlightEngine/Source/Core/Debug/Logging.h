// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

#ifdef _DEBUG // -----------------------------------------------------------------

// Libraries
#include <iostream>
#include <utility>

// Starlight Engine
#include "Framework/String.h"

// Log message
#define SL_LOG(category, type, message) Debug::Log(category, type, message)

// Log message with function name
#define SL_LOG_FUNC(category, type, message) SL_LOG(category, type, FString(__FUNCTION__) + " - " + (message))

enum ELogType : Uint8
{
	Debug,
	Display,
	Warning,
	Error
};

// BHH TODO: Update to some sort of class or struct later on.
enum ELogCategory : Uint8
{
	LogTemp,
	LogMain,
	LogEngine,
	LogInputManager,
	LogRenderer,
	LogMaths,
	LogSObject,
	LogSWorld,
	LogSGameInstance
};

static FString GetCategoryString(ELogCategory Category)
{
	switch (Category)
	{
	case LogTemp:
		return "Temp";
	case LogMain:
		return "LogMain";
	case LogEngine:
		return "LogEngine";
	case LogInputManager:
		return "LogInputManager";
	case LogRenderer:
		return "LogRenderer";
	case LogMaths:
		return "LogMaths";
	case LogSObject:
		return "LogSObject";
	case LogSWorld:
		return "LogSWorld";
	case LogSGameInstance:
		return "LogSGameInstance";
	}

	return "LogUnknown";
}

class Debug
{
public:
	static void Log(const ELogCategory Category, const ELogType Type, const FString& Message)
	{
		FString CategoryString = GetCategoryString(Category);

		switch (Type)
		{
		case ELogType::Debug:
			std::cout << "SL: [" + CategoryString + "]: " + Message << std::endl;
			break;
		case Warning:
			std::cout << "SL <WARNING>: [" + CategoryString + "]: " + Message << std::endl;
			break;
		case Error:
			std::cerr << "SL <ERROR>: [" + CategoryString + "]: " + Message << std::endl;
			break;
		case Display:
		default:
			std::cout << "SL: [" + CategoryString + "]: " + Message << std::endl;
			break;
		}
	}
};

struct DebugFunctionScope
{
	DebugFunctionScope(const ELogCategory InCategory, const ELogType InType, const FString& InFunctionName): m_category(InCategory), m_type(InType), m_functionName(InFunctionName)
	{
		SL_LOG(m_category, m_type, "\"" + m_functionName + "\" Started");
	}

	DebugFunctionScope(const ELogCategory InCategory, const FString& InFunctionName) : DebugFunctionScope(InCategory, Debug, InFunctionName) {}

	~DebugFunctionScope()
	{
		SL_LOG(m_category, m_type, "\"" + m_functionName + "\" Ended");
	}

private:
	ELogCategory m_category;
	ELogType m_type;
	FString m_functionName;
};

#define SL_LOG_FUNC_SCOPE(category, type) DebugFunctionScope DebugFunctionScope_##__FUNCTION__ = DebugFunctionScope(category, type, __FUNCTION__)

static FString GetSDLErrorFString()
{
	return FString(SDL_GetError());
}

#define SDL_GetErrorFString() GetSDLErrorFString()

#else // -----------------------------------------------------------------

// logs are compiled out
#define SL_LOG(category, type, message)
#define SL_LOG_FUNC(category, type, message)
#define SL_LOG_FUNC_SCOPE(category, type)
#define SDL_GetErrorFString()

#endif // -----------------------------------------------------------------
