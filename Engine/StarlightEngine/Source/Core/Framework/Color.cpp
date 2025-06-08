// Copyright © 2025 Bman, Inc. All rights reserved.

// Header
#include "Color.h"

// Starlight Engine
#include "Math/Math.h"

FRenderColor FRenderColor::operator+(const FRenderColor& Other) const
{
	FRenderColor Result = *this;
	Result += Other;
	return Result;
}

FRenderColor& FRenderColor::operator+=(const FRenderColor& Other)
{
	R = SMath::Clamp<Uint8>(R + Other.R, 0, 255);
	G = SMath::Clamp<Uint8>(G + Other.G, 0, 255);
	B = SMath::Clamp<Uint8>(B + Other.B, 0, 255);
	A = SMath::Clamp<Uint8>(A + Other.A, 0, 255);

	return *this;
}
