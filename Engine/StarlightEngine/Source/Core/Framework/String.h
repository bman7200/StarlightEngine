// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <ostream>

// Wrapper class for all strings and string manipulation
struct FString
{
	FString();
	FString(const char* InString);
	FString(const FString& Other);
	FString(FString&& Other) noexcept;

	~FString();

	FString& operator=(const FString& Other);
	FString& operator=(FString&& Other) noexcept;
	FString& operator=(const char* InString);

	FString operator+(const FString& Other) const;
	FString& operator+=(const FString& Other);

	bool operator==(const FString& Other) const;
	bool operator!=(const FString& Other) const;

	char& operator[](size_t Index);
	const char& operator[](size_t Index) const;

	friend std::ostream& operator<<(std::ostream& Out, const FString& String);

	// Public Methods
	int GetLength() const { return static_cast<int>(Length); }
	bool IsEmpty() const { return Length == 0; }
	bool IsEmptyOrWhitespace() const;
	const char* CStr() const { return Data; }

	/**
	 * @brief Removes leading and trailing whitespace from the string in-place.
	 */
	void TrimWhitespace();

	void Clear();

private:
	char* Data;
	size_t Length;
};
