// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <type_traits>

// Starlight Engine
#include "Pointers.h"

// Forward Declaration
class SObject;

// SObject Inheritance Check
template <typename T>
struct is_sobject_derived
{
	static constexpr bool value = std::is_base_of<SObject, T>::value;
};

// SObject Shared Pointer
template <typename T>
using TObjectPtr = std::enable_if_t<is_sobject_derived<T>::value, TSharedPtr<T>>;

// SObject Weak Pointer
template <typename T>
using TObjectWeakPtr = std::enable_if_t<is_sobject_derived<T>::value, TWeakPtr<T>>;

using SObjectPtr = TObjectPtr<SObject>;
using SObjectWeakPtr = TObjectWeakPtr<SObject>;

template <typename T>
static TObjectPtr<T> NewObject(SObjectPtr Outer)
{
	static_assert(is_sobject_derived<T>::value, "NewObject can only be used with types derived from SObject");
	return std::make_shared<T>(Outer);
}
