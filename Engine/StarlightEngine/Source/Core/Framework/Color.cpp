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
	R += Other.R;
	G += Other.G;
	B += Other.B;
	A += Other.A;
	return *this;
}

FRenderColor FRenderColor::operator-(const FRenderColor& Other) const
{
	FRenderColor Result = *this;
	Result -= Other;
	return Result;
}

FRenderColor& FRenderColor::operator-=(const FRenderColor& Other)
{
	R -= Other.R;
	G -= Other.G;
	B -= Other.B;
	A -= Other.A;
	return *this;
}

FRenderColor FRenderColor::operator*(const FRenderColor& Other) const
{
	FRenderColor Result = *this;
	Result *= Other;
	return Result;
}

FRenderColor& FRenderColor::operator*=(const FRenderColor& Other)
{
	R *= Other.R;
	G *= Other.G;
	B *= Other.B;
	A *= Other.A;
	return *this;
}

FRenderColor FRenderColor::operator/(const FRenderColor& Other) const
{
	FRenderColor Result = *this;
	Result /= Other;
	return Result;
}

FRenderColor& FRenderColor::operator/=(const FRenderColor& Other)
{
	R /= Other.R;
	G /= Other.G;
	B /= Other.B;
	A /= Other.A;
	return *this;
}

FRenderColor FRenderColor::operator*(const float Value) const
{
	FRenderColor Result = *this;
	Result *= Value;
	return Result;
}

FRenderColor& FRenderColor::operator*=(const float Value)
{
	R *= Value;
	G *= Value;
	B *= Value;
	A *= Value;
	return *this;
}

FRenderColor FRenderColor::operator/(const float Value) const
{
	FRenderColor Result = *this;
	Result /= Value;
	return Result;
}

FRenderColor& FRenderColor::operator/=(const float Value)
{
	R /= Value;
	G /= Value;
	B /= Value;
	A /= Value;
	return *this;
}

FHueColor FRenderColor::ToHueColor() const
{
	return FRenderColorToFHueColor(*this);
}

FRenderColor::operator FHueColor() const
{
	return ToHueColor();
}

FRenderColor FRenderColor::Clamped() const
{
	FRenderColor Result = *this;
	Result.R = SMath::Clamp<float>(R, 0.f, 1.f);
	Result.G = SMath::Clamp<float>(G, 0.f, 1.f);
	Result.B = SMath::Clamp<float>(B, 0.f, 1.f);
	Result.A = SMath::Clamp<float>(A, 0.f, 1.f);
	return Result;
}

FHueColor FHueColor::operator+(const FHueColor& Other) const
{
	FHueColor Result = *this;
	Result += Other;
	return Result;
}

FHueColor& FHueColor::operator+=(const FHueColor& Other)
{
	H = SMath::Mod(H + Other.H, 360.f);
	S += Other.S;
	V += Other.V;
	A += Other.A;
	return *this;
}

FHueColor FHueColor::operator-(const FHueColor& Other) const
{
	FHueColor Result = *this;
	Result -= Other;
	return Result;
}

FHueColor& FHueColor::operator-=(const FHueColor& Other)
{
	H = SMath::Mod(H - Other.H, 360.f);
	S -= Other.S;
	V -= Other.V;
	A -= Other.A;
	return *this;
}

FHueColor FHueColor::operator*(const FHueColor& Other) const
{
	FHueColor Result = *this;
	Result *= Other;
	return Result;
}

FHueColor& FHueColor::operator*=(const FHueColor& Other)
{
	H = SMath::Mod(H * Other.H, 360.f);
	S *= Other.S;
	V *= Other.V;
	A *= Other.A;
	return *this;
}

FHueColor FHueColor::operator/(const FHueColor& Other) const
{
	FHueColor Result = *this;
	Result /= Other;
	return Result;
}

FHueColor& FHueColor::operator/=(const FHueColor& Other)
{
	H = SMath::Mod(H / Other.H, 360.f);
	S /= Other.S;
	V /= Other.V;
	A /= Other.A;
	return *this;
}

FHueColor FHueColor::operator*(const float Value) const
{
	FHueColor Result = *this;
	Result *= Value;
	return Result;
}

FHueColor& FHueColor::operator*=(const float Value)
{
	H = SMath::Mod(H * Value, 360.f);
	S *= Value;
	V *= Value;
	A *= Value;
	return *this;
}

FHueColor FHueColor::operator/(const float Value) const
{
	FHueColor Result = *this;
	Result /= Value;
	return Result;
}

FHueColor& FHueColor::operator/=(const float Value)
{
	H = SMath::Mod(H / Value, 360.f);
	S /= Value;
	V /= Value;
	A /= Value;
	return *this;
}

FRenderColor FHueColor::ToRenderColor() const
{
	return FHueColorToFRenderColor(*this);
}

FHueColor::operator FRenderColor() const
{
	return ToRenderColor();
}

FHueColor FHueColor::Clamped() const
{
	FHueColor Result = *this;
	Result.H = SMath::Clamp<float>(H, 0.f, 360.f);
	Result.S = SMath::Clamp<float>(S, 0.f, 1.f);
	Result.V = SMath::Clamp<float>(V, 0.f, 1.f);
	Result.A = SMath::Clamp<float>(A, 0.f, 1.f);
	return Result;
}

FHueColor FRenderColorToFHueColor(const FRenderColor& InColor)
{
	using SMath::NearlyEqual;

	FHueColor OutColor;
	OutColor.A = InColor.A; // Alpha is copied directly

	const float R = InColor.R;
	const float G = InColor.G;
	const float B = InColor.B;

	const float CMax = SMath::Max(R, G, B);
	const float CMin = SMath::Min(R, G, B);
	const float Delta = CMax - CMin;

	// Hue calculation
	if (NearlyEqual(Delta, 0.0f))
	{
		OutColor.H = 0.0f; // Grayscale, hue is undefined but typically set to 0
	}
	else if (NearlyEqual(CMax, R))
	{
		OutColor.H = 60.0f * SMath::Mod(((G - B) / Delta), 6.0f);
	}
	else if (NearlyEqual(CMax, G))
	{
		OutColor.H = 60.0f * (((B - R) / Delta) + 2.0f);
	}
	else if (NearlyEqual(CMax, B))
	{
		OutColor.H = 60.0f * (((R - G) / Delta) + 4.0f);
	}

	if (OutColor.H < 0.0f)
	{
		OutColor.H += 360.0f;
	}

	// Saturation calculation
	OutColor.S = (CMax == 0.0f) ? 0.0f : (Delta / CMax);

	// Value calculation
	OutColor.V = CMax;

	return OutColor;
}

FRenderColor FHueColorToFRenderColor(const FHueColor& InColor)
{
	FRenderColor OutColor;
	OutColor.A = InColor.A; // Alpha is copied directly

	const float H = InColor.H;
	const float S = InColor.S;
	const float V = InColor.V;

	if (SMath::NearlyEqual(S, 0.0f))
	{
		// Grayscale, so R, G, and B are all equal to Value.
		OutColor.R = V;
		OutColor.G = V;
		OutColor.B = V;
		return OutColor;
	}

	const float C = V * S;
	const float H_Prime = SMath::Mod(H / 60.0f, 6.0f);
	const float X = C * (1.0f - SMath::Abs(SMath::Mod(H_Prime, 2.0f) - 1.0f));
	const float M = V - C;

	if (H_Prime >= 0.0f && H_Prime < 1.0f)
	{
		OutColor.R = C;
		OutColor.G = X;
		OutColor.B = 0;
	}
	else if (H_Prime >= 1.0f && H_Prime < 2.0f)
	{
		OutColor.R = X;
		OutColor.G = C;
		OutColor.B = 0;
	}
	else if (H_Prime >= 2.0f && H_Prime < 3.0f)
	{
		OutColor.R = 0;
		OutColor.G = C;
		OutColor.B = X;
	}
	else if (H_Prime >= 3.0f && H_Prime < 4.0f)
	{
		OutColor.R = 0;
		OutColor.G = X;
		OutColor.B = C;
	}
	else if (H_Prime >= 4.0f && H_Prime < 5.0f)
	{
		OutColor.R = X;
		OutColor.G = 0;
		OutColor.B = C;
	}
	else if (H_Prime >= 5.0f && H_Prime < 6.0f)
	{
		OutColor.R = C;
		OutColor.G = 0;
		OutColor.B = X;
	}

	OutColor.R += M;
	OutColor.G += M;
	OutColor.B += M;

	return OutColor;
}
