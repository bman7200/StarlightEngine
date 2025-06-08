// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_stdinc.h>

// Starlight Engine
#include "Math/Math.h"

// Forward Declare
struct FHueColor;

// Struct to store color
struct FRenderColor
{
	float R;
	float G;
	float B;
	float A;

	// Default empty constructor (White)
	FRenderColor() : R(1.f), G(1.f), B(1.f), A(1.f) {}

	// Copies another render color.
	FRenderColor(const FRenderColor& RenderColor) = default;

	// Copies another render color but with the alpha overwritten with a new value from 0 to 1.
	FRenderColor(const FRenderColor& RenderColor, const float A) : R(RenderColor.R), G(RenderColor.G), B(RenderColor.B), A(A) {}

	// Initialise all colors manually, RGBA values range from 0 to 1 each.
	FRenderColor(const float R, const float G, const float B, const float A = 1.f) : R(R), G(G), B(B), A(A) {}

	// Greyscale constructor
	FRenderColor(const float Value, const float A = 1.f) : R(Value), G(Value), B(Value), A(A) {}

	FRenderColor operator+(const FRenderColor& Other) const;
	FRenderColor& operator+=(const FRenderColor& Other);
	FRenderColor operator-(const FRenderColor& Other) const;
	FRenderColor& operator-=(const FRenderColor& Other);
	FRenderColor operator*(const FRenderColor& Other) const;
	FRenderColor& operator*=(const FRenderColor& Other);
	FRenderColor operator/(const FRenderColor& Other) const;
	FRenderColor& operator/=(const FRenderColor& Other);

	FRenderColor operator*(float Value) const;
	FRenderColor& operator*=(float Value);
	FRenderColor operator/(float Value) const;
	FRenderColor& operator/=(float Value);

	operator SDL_Color() const
	{
		FRenderColor Result = Clamped();
		return {
			static_cast<Uint8>(Result.R * 255.f),
			static_cast<Uint8>(Result.G * 255.f),
			static_cast<Uint8>(Result.B * 255.f),
			static_cast<Uint8>(Result.A * 255.f)
		};
	}

	FHueColor ToHueColor() const;
	operator FHueColor() const;

	FRenderColor Clamped() const;
};

namespace ERenderColors
{
const FRenderColor BlackTransparent(0.f, 0.f);
const FRenderColor WhiteTransparent(255.f, 0.f);

const FRenderColor Black(0.f);
const FRenderColor DarkGray(255.f * 0.25f);
const FRenderColor Gray(255.f * 0.50f);
const FRenderColor LightGray(255.f * 0.75f);
const FRenderColor White(255.f);

const FRenderColor Red(255.f, 0.f, 0.f);
const FRenderColor Yellow(255.f, 255.f, 0.f);
const FRenderColor Green(0.f, 255.f, 0.f);
const FRenderColor Cyan(0.f, 255.f, 255.f);
const FRenderColor Blue(0.f, 0.f, 255.f);
const FRenderColor Magenta(255.f, 0.f, 255.f);
}

struct FHueColor
{
	float H;
	float S;
	float V;
	float A;

	// Default empty constructor (White)
	FHueColor() : H(0.f), S(0.f), V(1.f), A(1.f) {}

	// Copies another render color.
	FHueColor(const FHueColor& HueColor) = default;

	// Copies another render color but with the alpha overwritten with a new value from 0.0f to 1.0f.
	FHueColor(const FHueColor& HueColor, const float A) : H(HueColor.H), S(HueColor.S), V(HueColor.V), A(A) {}

	/**
	 * @brief Initialise all colors manually, with default opaque alpha.
	 * @param H Hue: 0 to 360
	 * @param S Saturation: 0 to 1
	 * @param V Value: 0 to 1
	 * @param A Alpha: 0 to 1
	 */
	FHueColor(const float H, const float S, const float V, const float A = 1.f) : H(SMath::Mod(H, 360.f)), S(S), V(V), A(A) {}

	// Greyscale constructor
	FHueColor(const float V, const float A = 1.f) : H(0.f), S(0.f), V(V), A(A) {}

	FHueColor operator+(const FHueColor& Other) const;
	FHueColor& operator+=(const FHueColor& Other);
	FHueColor operator-(const FHueColor& Other) const;
	FHueColor& operator-=(const FHueColor& Other);
	FHueColor operator*(const FHueColor& Other) const;
	FHueColor& operator*=(const FHueColor& Other);
	FHueColor operator/(const FHueColor& Other) const;
	FHueColor& operator/=(const FHueColor& Other);

	FHueColor operator*(float Value) const;
	FHueColor& operator*=(float Value);
	FHueColor operator/(float Value) const;
	FHueColor& operator/=(float Value);

	FRenderColor ToRenderColor() const;
	operator FRenderColor() const;

	FHueColor Clamped() const;
};

namespace EHueColors
{
const FHueColor Black(0.0f);
const FHueColor DarkGray(0.25f);
const FHueColor Gray(0.5f);
const FHueColor LightGray(0.75f);
const FHueColor White(1.0f);

const FHueColor Red(0.f / 360.f, 1.f, 1.f);
const FHueColor Yellow(60.f / 360.f, 1.f, 1.f);
const FHueColor Green(120.f / 360.f, 1.f, 1.f);
const FHueColor Cyan(180.f / 360.f, 1.f, 1.f);
const FHueColor Blue(240.f / 360.f, 1.f, 1.f);
const FHueColor Magenta(300.f / 360.f, 1.f, 1.f);
}

FHueColor FRenderColorToFHueColor(const FRenderColor& InColor);
FRenderColor FHueColorToFRenderColor(const FHueColor& InColor);
