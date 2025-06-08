// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <iostream>
#include <SDL3/SDL_stdinc.h>

#include "Input/InputKeys.h"


namespace SMath
{
// Define a small epsilon for floating point comparisons
constexpr float EPSILON = SDL_FLT_EPSILON;
constexpr float PI = SDL_PI_F;
constexpr float TWO_PI = 2.0f * PI;
constexpr float HALF_PI = 0.5f * PI;

// Absolute Value
inline float Abs(const float Value)
{
	return SDL_fabsf(Value);
}

// Check if floats are safely equal
inline bool NearlyEqual(const float A, const float B, const float Epsilon = EPSILON)
{
	return Abs(A - B) < Epsilon;
}

// Round
inline float Round(const float Value)
{
	return SDL_roundf(Value);
}

// Truncates the decimal. Basically, rounds towards zero.
inline float Trunc(const float Value)
{
	return SDL_truncf(Value);
}

inline float Floor(const float Value)
{
	return SDL_floorf(Value);
}

inline float Ceil(const float Value)
{
	return SDL_ceilf(Value);
}

inline float Mod(const float A, const float B)
{
	return SDL_fmodf(A, B);
}

inline float Clamp(const float Value, const float Min, const float Max)
{
	return SDL_clamp(Value, Min, Max);
}

inline float Min(const float A, const float B)
{
	return SDL_min(A, B);
}

inline float Max(const float A, const float B)
{
	return SDL_max(A, B);
}

// Returns the Value from A to B, depending on Alpha from 0 to 1 respectively.
inline float Lerp(const float A, const float B, const float Alpha)
{
	return (B - A) * Alpha + A;
}

// Gives you the Alpha from 0 to 1, depending on the Value from A to B respectively.
inline float InverseLerp(const float Value, const float A, const float B)
{
	if (NearlyEqual(A, B))
	{
		return 0;
	}

	return Value - A / (B - A);
}

// Remaps the Value proportionally from the Start range, to the End range.
inline float RemapRange(const float Value, const float StartMin, const float StartMax, const float EndMin, const float EndMax)
{
	if (NearlyEqual(StartMin, StartMax))
	{
		return EndMin;
	}

	return (Value - StartMin) / (StartMax - StartMin) * (EndMax - EndMin) + EndMin;
}

// Square Root
inline float Sqrt(const float Value)
{
	return SDL_sqrtf(Value);
}

// Power
inline float Power(const float Value, const float Power)
{
	return SDL_powf(Value, Power);
}

// Exponential
inline float Exp(const float Value)
{
	return SDL_expf(Value);
}

// Natural Logarithm
inline float Log(const float Value)
{
	return SDL_logf(Value);
}

/**
* @brief Converts degrees to radians.
* @param Degrees Angle in degrees.
* @return Angle in radians.
*/
inline float DegreesToRadians(const float Degrees)
{
	return Degrees * (PI / 180.0f);
}

/**
* @brief Converts radians to degrees.
* @param Radians Angle in radians.
* @return Angle in degrees.
*/
inline float RadiansToDegrees(const float Radians)
{
	return Radians * (180.0f / PI);
}

inline float Sin(const float Radians)
{
	return SDL_sinf(Radians);
}

inline float Cos(const float Radians)
{
	return SDL_cosf(Radians);
}

inline float Tan(const float Radians)
{
	return SDL_tanf(Radians);
}

inline float ASin(const float Radians)
{
	return SDL_asinf(Radians);
}

inline float ACos(const float Radians)
{
	return SDL_acosf(Radians);
}

inline float ATan(const float Radians)
{
	return SDL_atanf(Radians);
}

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
		return NearlyEqual(x, Other.x) && NearlyEqual(y, Other.y);
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
	float Length() const { return sqrtf(LengthSquared()); }

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
		if (Len > EPSILON)
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
};

// Global scalar multiplication for FVector2 (e.g., 5.0f * vec)
inline FVector2 operator*(const float scalar, const FVector2& vec)
{
	return FVector2(vec.x * scalar, vec.y * scalar);
}

// Stream insertion operator for easy printing of FVector2
inline std::ostream& operator<<(std::ostream& os, const FVector2& vec)
{
	os << "FVector2(" << vec.x << ", " << vec.y << ")";
	return os;
}

// The length between two FVector2 values.
inline float Vector2Distance(const FVector2& A, const FVector2& B)
{
	return (B - A).Length();
}

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
		return NearlyEqual(x, Other.x) && NearlyEqual(y, Other.y) && NearlyEqual(z, Other.z);
	}

	bool operator!=(const FVector3& Other) const
	{
		return !(*this == Other);
	}

	/**
	* @brief Calculates the squared magnitude (length) of the vector.
	* @return The squared magnitude.
	*/
	float LengthSquared() const { return x * x + y * y + z * z; }

	/**
	* @brief Calculates the magnitude (length) of the vector.
	* @return The magnitude.
	*/
	float Length() const { return sqrtf(LengthSquared()); }

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
		if (Len > EPSILON)
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
};

// Global scalar multiplication for FVector3 (e.g., 5.0f * vec)
inline FVector3 operator*(const float scalar, const FVector3& vec)
{
	return FVector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

// Stream insertion operator for easy printing of FVector3
inline std::ostream& operator<<(std::ostream& os, const FVector3& vec)
{
	os << "FVector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return os;
}

// The length between two FVector3 values.
inline float Vector3Distance(const FVector3& A, const FVector3& B)
{
	return (B - A).Length();
}
}
