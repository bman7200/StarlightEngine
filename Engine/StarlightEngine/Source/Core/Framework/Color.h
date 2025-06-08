// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL_stdinc.h>

// Struct to store color
struct FRenderColor
{
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;

	// Default empty constructor (White)
	FRenderColor() : R(255), G(255), B(255), A(255) {}

	// Copies another render color.
	FRenderColor(const FRenderColor& RenderColor) = default;

	// Copies another render color but with the alpha overwritten with a new value from 0-255.
	FRenderColor(const FRenderColor& RenderColor, const Uint8 A) : R(RenderColor.R), G(RenderColor.G), B(RenderColor.B), A(A) {}

	// Initialise all colors manually, RGBA values range from 0-255 each.
	FRenderColor(const Uint8 R, const Uint8 G, const Uint8 B, const Uint8 A = 255) : R(R), G(G), B(B), A(A) {}

	// Greyscale constructor
	FRenderColor(const Uint8 Value, const Uint8 A = 255) : R(Value), G(Value), B(Value), A(A) {}

	FRenderColor operator+(const FRenderColor& Other) const;
	FRenderColor& operator+=(const FRenderColor& Other);
};

namespace ERenderColors
{
const FRenderColor BlackTransparent(0, 0);
const FRenderColor WhiteTransparent(255, 0);

const FRenderColor Black(0);
const FRenderColor Gray(255 / 2);
const FRenderColor White(255);

const FRenderColor Red(255, 0, 0);
const FRenderColor Yellow(255, 255, 0);
const FRenderColor Green(0, 255, 0);
const FRenderColor Cyan(0, 255, 255);
const FRenderColor Blue(0, 0, 255);
const FRenderColor Magenta(255, 0, 255);
}

struct FHueColor
{
	float H;
	float S;
	float V;
	float A;

	// Default empty constructor (White)
	FHueColor() : H(0.0f), S(0.0f), V(1.0f), A(1.0f) {}

	// Copies another render color.
	FHueColor(const FHueColor& HueColor) = default;

	// Copies another render color but with the alpha overwritten with a new value from 0.0f to 1.0f.
	FHueColor(const FHueColor& HueColor, const float A) : H(HueColor.H), S(HueColor.S), V(HueColor.V), A(A) {}

	// Initialise all colors manually, HSVA values range from 0.0f to 1.0f each.
	FHueColor(const float H, const float S, const float V, const float A = 1.0f) : H(H), S(S), V(V), A(A) {}

	// Greyscale constructor
	FHueColor(const float V, const float A = 1.0f) : H(0.0f), S(0.0f), V(V), A(A) {}
};

namespace EHueColors
{
const FHueColor Black(0.0f);
const FHueColor Gray(0.5f);
const FHueColor White(1.0f);

const FHueColor Red(0.0f / 360.0f, 1.0f, 1.0f);
const FHueColor Yellow(60.0f / 360.0f, 1.0f, 1.0f);
const FHueColor Green(120.0f / 360.0f, 1.0f, 1.0f);
const FHueColor Cyan(180.0f / 360.0f, 1.0f, 1.0f);
const FHueColor Blue(240.0f / 360.0f, 1.0f, 1.0f);
const FHueColor Magenta(300.0f / 360.0f, 1.0f, 1.0f);
}
