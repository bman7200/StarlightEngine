// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <ostream>
#include <string>

// Wrapper class for all strings and string manipulation
struct FString
{
	FString();
	FString(const char* InString);
	FString(const FString& Other);
	FString(FString&& Other) noexcept;

	FString(const std::string& InString) : FString(InString.c_str()) {}

	~FString();

	FString& operator=(const FString& Other);
	FString& operator=(FString&& Other) noexcept;
	FString& operator=(const char* InString);

	FString operator+(const FString& Other) const;
	FString operator+(const char* InString) const;
	FString& operator+=(const FString& Other);
	FString& operator+=(const char* InString);

	bool operator==(const FString& Other) const;
	bool operator!=(const FString& Other) const;

	char& operator[](size_t Index);
	const char& operator[](size_t Index) const;

	friend std::ostream& operator<<(std::ostream& Out, const FString& String);

	operator const std::string() const { return Data; }
	operator const char*() const { return CStr(); }

	// Public Methods
	int GetLength() const { return static_cast<int>(Length); }
	bool IsEmpty() const { return Length == 0; }
	bool IsEmptyOrWhitespace() const;
	const char* CStr() const { return Data; }

	/**
	 * @brief Removes leading and trailing whitespace from the string in-place.
	 */
	void TrimWhitespace();

	/**
	 * @brief Removes a specified number of characters from the start or end of the string.
	 * @param Count The number of characters to remove.
	 * @param bFromStart If true, removes from the start; if false, removes from the end.
	 */
	void RemoveChars(int Count, bool bFromStart = true);

	void Clear();

private:
	char* Data;
	size_t Length;

public:
	FString(const int Value) : FString(std::to_string(Value).c_str()) {}
	FString(const float Value) : FString(std::to_string(Value).c_str()) {}

	template <typename T>
	FString(const T& Object) : FString(Object.ToString()) {}
};

FString operator+(const char* InString, const FString& Other);
