// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <memory>

template <class T>
using TSharableClass = std::enable_shared_from_this<T>;

template <class T>
using TUniquePtr = std::unique_ptr<T>;

template <class T>
using TSharedPtr = std::shared_ptr<T>;

template <class T>
using TWeakPtr = std::weak_ptr<T>;

template <class T, class... Types>
TSharedPtr<T> TMakeShared(Types&&... Args)
{
	return std::make_shared<T>(_STD forward<Types>(Args)...);
}
