// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "String.h"

// Libraries
#include <cstring>
#include <locale>

FString::FString()
	: Data(new char[1]), Length(0)
{
	Data[0] = '\0'; // Null-terminate empty string.
}

FString::FString(const char* InString)
{
	if (InString)
	{
		Length = strlen(InString);
		Data = new char[Length + 1]; // +1 for the null terminator
		strcpy_s(Data, Length + 1, InString);
	}
	else
	{
		*this = FString();
	}
}

FString::FString(const FString& Other)
	: Length(Other.Length)
{
	Data = new char[Length + 1];
	strcpy_s(Data, Length + 1, Other.Data);
}

FString::FString(FString&& Other) noexcept
	: Data(Other.Data), Length(Other.Length)
{
	Other.Data = nullptr;
	Other.Length = 0;
}

FString::~FString()
{
	delete[] Data;
}

FString& FString::operator=(const FString& Other)
{
	if (this != &Other)
	{
		delete[] Data;

		Length = Other.Length;
		Data = new char[Length + 1];
		strcpy_s(Data, Length + 1, Other.Data);
	}
	return *this;
}

FString& FString::operator=(FString&& Other) noexcept
{
	if (this != &Other)
	{
		delete[] Data;

		Data = Other.Data;
		Length = Other.Length;

		Other.Data = nullptr;
		Other.Length = 0;
	}
	return *this;
}

FString& FString::operator=(const char* InString)
{
	delete[] Data;
	if (InString)
	{
		Length = strlen(InString);
		Data = new char[Length + 1];
		strcpy_s(Data, Length + 1, InString);
	}
	else
	{
		*this = FString();
	}
	return *this;
}

FString FString::operator+(const FString& Other) const
{
	FString NewString;
	NewString.Length = Length + Other.Length;
	delete[] NewString.Data;
	NewString.Data = new char[NewString.Length + 1];

	strcpy_s(NewString.Data, NewString.Length + 1, Data);
	strcat_s(NewString.Data, NewString.Length + 1, Other.Data);

	return NewString;
}

FString FString::operator+(const char* InString) const
{
	FString NewString;
	NewString.Length = Length + strlen(InString);
	delete[] NewString.Data;
	NewString.Data = new char[NewString.Length + 1];

	strcpy_s(NewString.Data, NewString.Length + 1, Data);
	strcat_s(NewString.Data, NewString.Length + 1, InString);

	return NewString;
}

FString& FString::operator+=(const FString& Other)
{
	if (Other.Length == 0)
	{
		return *this;
	}

	size_t NewLength = Length + Other.Length;
	auto NewData = new char[NewLength + 1];

	strcpy_s(NewData, NewLength + 1, Data);
	strcat_s(NewData, NewLength + 1, Other.Data);

	delete[] Data;

	Data = NewData;
	Length = NewLength;

	return *this;
}

FString& FString::operator+=(const char* InString)
{
	if (strlen(InString) == 0)
	{
		return *this;
	}

	size_t NewLength = Length + strlen(InString);
	auto NewData = new char[NewLength + 1];

	strcpy_s(NewData, NewLength + 1, Data);
	strcat_s(NewData, NewLength + 1, InString);

	delete[] Data;

	Data = NewData;
	Length = NewLength;

	return *this;
}

bool FString::operator==(const FString& Other) const
{
	if (Length != Other.Length)
	{
		return false;
	}
	return strcmp(Data, Other.Data) == 0;
}

bool FString::operator!=(const FString& Other) const
{
	return !(*this == Other);
}

char& FString::operator[](size_t Index)
{
	return Data[Index];
}

const char& FString::operator[](size_t Index) const
{
	return Data[Index];
}

std::ostream& operator<<(std::ostream& Out, const FString& String)
{
	Out << String.Data;
	return Out;
}

bool FString::IsEmptyOrWhitespace() const
{
	if (IsEmpty())
	{
		return true;
	}

	for (size_t Index = 0; Index < Length; ++Index)
	{
		// isspace checks for spaces, tabs, newlines, etc.
		if (false == std::isspace(static_cast<unsigned char>(Data[Index])))
		{
			return false;
		}
	}

	return true;
}

void FString::TrimWhitespace()
{
	if (IsEmpty())
	{
		return;
	}

	size_t First = 0;
	while (First < Length && isspace(static_cast<unsigned char>(Data[First])))
	{
		First++;
	}

	size_t Last = Length - 1;
	while (Last > First && isspace(static_cast<unsigned char>(Data[Last])))
	{
		Last--;
	}

	const size_t NewLength = Last - First + 1;

	if (First > 0)
	{
		memmove(Data, &Data[First], NewLength);
	}

	Length = NewLength;
	Data[Length] = '\0';
}

void FString::Clear()
{
	Length = 0;
	Data[0] = '\0';
}

FString operator+(const char* InString, const FString& Other)
{
	return FString(InString) + Other;
}
