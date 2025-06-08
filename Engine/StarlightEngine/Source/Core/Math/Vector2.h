// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "Math.h"
#include "Framework/String.h"

/**
* @struct FVector2
* @brief Represents a 2D vector or point.
*/
struct FVector2
{
	float x;
	float y;

	// Constructors
	FVector2() : x(0.0f), y(0.0f) {}
	FVector2(const float _unit) : x(_unit), y(_unit) {}
	FVector2(const float _x, const float _y) : x(_x), y(_y) {}

	// Operator Overloads for FVector2
	FVector2 operator+(const FVector2& Other) const { return FVector2(x + Other.x, y + Other.y); }
	FVector2 operator-(const FVector2& Other) const { return FVector2(x - Other.x, y - Other.y); }
	FVector2 operator*(const float scalar) const { return FVector2(x * scalar, y * scalar); }
	FVector2 operator/(const float scalar) const { return FVector2(x / scalar, y / scalar); }

	FVector2& operator+=(const FVector2& Other)
	{
		x += Other.x;
		y += Other.y;
		return *this;
	}

	FVector2& operator-=(const FVector2& Other)
	{
		x -= Other.x;
		y -= Other.y;
		return *this;
	}

	FVector2& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	FVector2& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	bool operator==(const FVector2& Other) const
	{
		return SMath::NearlyEqual(x, Other.x) && SMath::NearlyEqual(y, Other.y);
	}

	bool operator!=(const FVector2& Other) const
	{
		return !(*this == Other);
	}

	/**
	* @brief Calculates the squared magnitude (length) of the vector.
	* Useful for comparisons as it avoids a sqrt operation.
	* @return The squared magnitude.
	*/
	float LengthSquared() const { return x * x + y * y; }

	/**
	* @brief Calculates the magnitude (length) of the vector.
	* @return The magnitude.
	*/
	float Length() const { return SMath::Sqrt(LengthSquared()); }

	/**
	* @brief Normalizes the vector (makes its length 1).
	* @return Returns the new normalized value.
	*/
	FVector2 SetNormalized()
	{
		*this = Normalized();
		return *this;
	}

	/**
	* @brief Returns the normalized vector without affecting the value.
	* @returns The vector normalized.
	*/
	FVector2 Normalized() const
	{
		const float Len = Length();
		if (Len > SMath::EPSILON)
		{
			return *this / Len;
		}
		return FVector2(0.0f, 0.0f);
	}

	/**
	* @brief Calculates the dot product with another vector.
	* @param other The other vector.
	* @return The dot product.
	*/
	float Dot(const FVector2& other) const { return x * other.x + y * other.y; }

	FString ToString() const
	{
		return FString("(" +
			FString(x) + ", " +
			FString(y) + ")");
	}
};

// Global scalar multiplication for FVector2 (e.g., 5.0f * vec)
inline FVector2 operator*(const float scalar, const FVector2& vec)
{
	return FVector2(vec.x * scalar, vec.y * scalar);
}

template <>
struct std::hash<FVector2>
{
	size_t operator()(const FVector2& Vector) const noexcept
	{
		const size_t h1 = std::hash<float>{}(Vector.x);
		const size_t h2 = std::hash<float>{}(Vector.y);

		return h1 ^ (h2 << 1);
	}
};

namespace SMath
{
inline bool NearlyEqual(const FVector2& A, const FVector2& B, const float Epsilon)
{
	return Abs(B.x - A.x) < Epsilon && Abs(B.y - A.y) < Epsilon;
}

// The length between two FVector2 values.
inline float Vector2Distance(const FVector2& A, const FVector2& B)
{
	return (B - A).Length();
}
}
