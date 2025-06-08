// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <memory>

template <typename T>
using XSharedClass = std::enable_shared_from_this<T>;

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T>
using TWeakPtr = std::weak_ptr<T>;

template <typename T>
using TMakeShared = std::make_shared<T>;
