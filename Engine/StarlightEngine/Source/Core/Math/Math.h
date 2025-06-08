// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <iostream>
#include <SDL3/SDL_stdinc.h>

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
template <typename T>
bool NearlyEqual(const T A, const T B, const float Epsilon = EPSILON)
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

template <typename T = float>
T Clamp(const T Value, const T Min, const T Max)
{
	return SDL_clamp(Value, Min, Max);
}

template <typename T = float>
T Min(const T A, const T B)
{
	return SDL_min(A, B);
}

template <typename T = float>
T Min(const T A, const T B, const T C)
{
	return Min(Min(A, B), C);
}

template <typename T = float>
T Max(const T A, const T B)
{
	return SDL_max(A, B);
}

template <typename T = float>
T Max(const T A, const T B, const T C)
{
	return Max(Max(A, B), C);
}

// Returns the Value from A to B, depending on Alpha from 0 to 1 respectively.
template <typename T = float>
T Lerp(const T A, const T B, const float Alpha)
{
	return (B - A) * Alpha + A;
}

// Gives you the Alpha from 0 to 1, depending on the Value from A to B respectively.
template <typename T = float>
float InverseLerp(const T Value, const T A, const T B)
{
	if (NearlyEqual(A, B))
	{
		return 0.0f;
	}

	return Value - A / (B - A);
}

// Remaps the Value proportionally from the Start range, to the End range.
template <typename T = float>
T RemapRange(const T Value, const T StartMin, const T StartMax, const T EndMin, const T EndMax)
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
inline float Ln(const float Value)
{
	return SDL_logf(Value);
}

// Log base 10
inline float Log10(const float Value)
{
	return SDL_log10f(Value);
}

// Log with custom base
inline float Log(const float Value, const float Base)
{
	return SDL_logf(Value) / SDL_logf(Base);
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
}
