// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <memory>
#include <type_traits>

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
using TObjectPtr = std::enable_if_t<is_sobject_derived<T>::value, std::shared_ptr<T>>;

// SObject Weak Pointer
template <typename T>
using TObjectWeakPtr = std::enable_if_t<is_sobject_derived<T>::value, std::weak_ptr<T>>;

using SObjectPtr = TObjectPtr<SObject>;
using SObjectWeakPtr = TObjectWeakPtr<SObject>;

template <typename T>
static TObjectPtr<T> NewObject(SObjectPtr Outer)
{
	return std::make_shared<T>(Outer);
}
