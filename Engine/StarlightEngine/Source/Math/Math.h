// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <cmath>
#include <iostream>
#include <limits>


namespace Math
{
	// Define a small epsilon for floating point comparisons
	constexpr float EPSILON = std::numeric_limits<float>::epsilon();
	constexpr float PI = 3.14159265359f;
	constexpr float TWO_PI = 2.0f * PI;
	constexpr float HALF_PI = 0.5f * PI;

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

	/**
	 * @struct Vector2
	 * @brief Represents a 2D vector or point.
	 */
	struct Vector2
	{
		float x;
		float y;

		// Constructors
		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(const float _unit) : x(_unit), y(_unit) {}
		Vector2(const float _x, const float _y) : x(_x), y(_y) {}

		// Operator Overloads for Vector2
		Vector2 operator+(const Vector2& Other) const { return Vector2(x + Other.x, y + Other.y); }
		Vector2 operator-(const Vector2& Other) const { return Vector2(x - Other.x, y - Other.y); }
		Vector2 operator*(const float scalar) const { return Vector2(x * scalar, y * scalar); }
		Vector2 operator/(const float scalar) const { return Vector2(x / scalar, y / scalar); }

		Vector2& operator+=(const Vector2& Other)
		{
			x += Other.x;
			y += Other.y;
			return *this;
		}

		Vector2& operator-=(const Vector2& Other)
		{
			x -= Other.x;
			y -= Other.y;
			return *this;
		}

		Vector2& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		bool operator==(const Vector2& Other) const
		{
			return fabsf(x - Other.x) < EPSILON && fabsf(y - Other.y) < EPSILON;
		}

		bool operator!=(const Vector2& Other) const
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
		 * @return A new normalized Vector2.
		 */
		Vector2 Normalize() const
		{
			const float Len = Length();
			if (Len > EPSILON)
			{
				// Avoid division by zero
				return *this / Len;
			}
			return Vector2(0.0f, 0.0f); // Return zero vector if length is zero
		}

		/**
		 * @brief Calculates the dot product with another vector.
		 * @param other The other vector.
		 * @return The dot product.
		 */
		float Dot(const Vector2& other) const { return x * other.x + y * other.y; }
	};

	// Global scalar multiplication for Vector2 (e.g., 5.0f * vec)
	inline Vector2 operator*(const float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	// Stream insertion operator for easy printing of Vector2
	inline std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		os << "Vector2(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	// The length between two Vector2 values.
	inline float Vector2Distance(const Vector2& A, const Vector2& B)
	{
		return (B - A).Length();
	}

	/**
	 * @struct Vector3
	 * @brief Represents a 3D vector or point.
	 */
	struct Vector3
	{
		float x;
		float y;
		float z;

		// Constructors
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(const float _unit) : x(_unit), y(_unit), z(_unit) {}
		Vector3(const float _x = 0, const float _y = 0, const float _z = 0) : x(_x), y(_y), z(_z) {}
		Vector3(const Vector2& Vector2, const float _z = 0) : x(Vector2.x), y(Vector2.y), z(_z) {} // From Vector2 and z

		// Operator Overloads for Vector3
		Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
		Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
		Vector3 operator*(const float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
		Vector3 operator/(const float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

		Vector3& operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3& operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3& operator*=(const float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vector3& operator/=(const float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		bool operator==(const Vector3& other) const
		{
			return fabsf(x - other.x) < EPSILON && fabsf(y - other.y) < EPSILON && fabsf(z - other.z) < EPSILON;
		}

		bool operator!=(const Vector3& other) const
		{
			return !(*this == other);
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
		 * @return A new normalized Vector3.
		 */
		Vector3 Normalize() const
		{
			const float Len = Length();
			if (Len > EPSILON)
			{
				// Avoid division by zero
				return *this / Len;
			}
			return Vector3(0.0f, 0.0f, 0.0f); // Return zero vector if length is zero
		}

		/**
		 * @brief Calculates the dot product with another vector.
		 * @param other The other vector.
		 * @return The dot product.
		 */
		float Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }

		/**
		 * @brief Calculates the cross product with another vector.
		 * @param other The other vector.
		 * @return A new Vector3 representing the cross product.
		 */
		Vector3 Cross(const Vector3& other) const
		{
			return Vector3(
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
				);
		}
	};

	// Global scalar multiplication for Vector3 (e.g., 5.0f * vec)
	inline Vector3 operator*(const float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Stream insertion operator for easy printing of Vector3
	inline std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

	// The length between two Vector3 values.
	inline float Vector3Distance(const Vector3& A, const Vector3& B)
	{
		return (B - A).Length();
	}
}
