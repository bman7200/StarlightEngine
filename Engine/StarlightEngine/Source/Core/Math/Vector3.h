// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Starlight Engine
#include "Math.h"
#include "Framework/String.h"

/**
* @struct FVector3
* @brief Represents a 3D vector or point.
*/
struct FVector3
{
	float x;
	float y;
	float z;

	// Constructors
	FVector3() : x(0.0f), y(0.0f), z(0.0f) {}
	FVector3(const float _unit) : x(_unit), y(_unit), z(_unit) {}
	FVector3(const float _x = 0, const float _y = 0, const float _z = 0) : x(_x), y(_y), z(_z) {}
	FVector3(const FVector2& Vector2, const float _z = 0) : x(Vector2.x), y(Vector2.y), z(_z) {} // From FVector2 and z

	// Operator Overloads for FVector3
	FVector3 operator+(const FVector3& other) const { return FVector3(x + other.x, y + other.y, z + other.z); }
	FVector3 operator-(const FVector3& other) const { return FVector3(x - other.x, y - other.y, z - other.z); }
	FVector3 operator*(const float scalar) const { return FVector3(x * scalar, y * scalar, z * scalar); }
	FVector3 operator/(const float scalar) const { return FVector3(x / scalar, y / scalar, z / scalar); }

	FVector3& operator+=(const FVector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	FVector3& operator-=(const FVector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	FVector3& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	FVector3& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	bool operator==(const FVector3& Other) const
	{
		return SMath::NearlyEqual(x, Other.x) && SMath::NearlyEqual(y, Other.y) && SMath::NearlyEqual(z, Other.z);
	}

	bool operator!=(const FVector3& Other) const
	{
		return !(*this == Other);
	}

	/**
	* @brief Calculates the squared magnitude (length) of the vector.
	* Useful for comparisons as it avoids a sqrt operation.
	* @return The squared magnitude.
	*/
	float LengthSquared() const { return x * x + y * y + z * z; }

	/**
	* @brief Calculates the magnitude (length) of the vector.
	* @return The magnitude.
	*/
	float Length() const { return SMath::Sqrt(LengthSquared()); }

	/**
	* @brief Normalizes the vector (makes its length 1).
	* @return Returns the new normalized value.
	*/
	FVector3 SetNormalized()
	{
		*this = Normalized();
		return *this;
	}

	/**
	* @brief Returns the normalized vector without affecting the value.
	* @returns The vector normalized.
	*/
	FVector3 Normalized() const
	{
		const float Len = Length();
		if (Len > SMath::EPSILON)
		{
			return *this / Len;
		}
		return FVector3(0.0f, 0.0f);
	}

	/**
	* @brief Calculates the dot product with another vector.
	* @param other The other vector.
	* @return The dot product.
	*/
	float Dot(const FVector3& other) const { return x * other.x + y * other.y + z * other.z; }

	/**
	* @brief Calculates the cross product with another vector.
	* @param other The other vector.
	* @return A new Vector3 representing the cross product.
	*/
	FVector3 Cross(const FVector3& other) const
	{
		return FVector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
			);
	}

	FString ToString() const
	{
		return FString("(" +
			FString(x) + ", " +
			FString(y) + ", " +
			FString(z) + ")");
	}
};

// Global scalar multiplication for FVector3 (e.g., 5.0f * vec)
inline FVector3 operator*(const float scalar, const FVector3& vec)
{
	return FVector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

template <>
struct std::hash<FVector3>
{
	size_t operator()(const FVector3& Vector) const noexcept
	{
		const size_t h1 = std::hash<float>{}(Vector.x);
		const size_t h2 = std::hash<float>{}(Vector.y);
		const size_t h3 = std::hash<float>{}(Vector.z);

		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

namespace SMath
{
inline bool NearlyEqual(const FVector3& A, const FVector3& B, const float Epsilon)
{
	return Abs(B.x - A.x) < Epsilon && Abs(B.y - A.y) < Epsilon && Abs(B.z - A.z) < Epsilon;
}

// The length between two FVector3 values.
inline float Vector3Distance(const FVector3& A, const FVector3& B)
{
	return (B - A).Length();
}
}
