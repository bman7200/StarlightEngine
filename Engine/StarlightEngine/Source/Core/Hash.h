// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <functional>

/**
* @brief Combines a new hash value into an existing seed.
 * A robust hash-combining implementation modeled after boost::hash_combine.
 */
template <class T>
void HashCombine(size_t& seed, const T& v)
{
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
