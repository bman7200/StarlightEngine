// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>

enum class EInputKeyType : Uint8
{
	Unknown = 0,
	KeyboardButton,
	MouseButton,
	MouseAxis1D,
	MouseAxis2D,
	GamepadButton,
	GamepadJoystickAxis1D,
	GamepadJoystickAxis2D,
	GamepadTriggerAxis,
};

enum class EInputAxisOrientation : Uint8
{
	Unknown = 0,
	X,
	Y,
};

struct FInputGamepadAxisPair
{
	SDL_GamepadAxis Horizontal;
	SDL_GamepadAxis Vertical;

	explicit FInputGamepadAxisPair(const SDL_GamepadAxis Horizontal, const SDL_GamepadAxis Vertical) : Horizontal(Horizontal), Vertical(Vertical) {}

	bool operator==(const FInputGamepadAxisPair& Other) const
	{
		return Horizontal == Other.Horizontal && Vertical == Other.Vertical;
	}

	bool operator!=(const FInputGamepadAxisPair& Other) const
	{
		return !(*this == Other);
	}
};

struct FInputKey
{
	EInputKeyType Type;

	// Identifier from type
	union
	{
		Uint32 ButtonCode;
		EInputAxisOrientation AxisOrientation;
		SDL_GamepadButton GamepadButton;
		SDL_GamepadAxis GamepadAxis;
		FInputGamepadAxisPair GamepadAxisPair;
		int RawValue;
	};

	// Default Constructor
	FInputKey() : Type(EInputKeyType::Unknown), RawValue(0) {}

	// General
	explicit FInputKey(const EInputKeyType Type) : Type(Type), RawValue(0) {}

	// Keyboard / Mouse Button
	explicit FInputKey(const Uint32 ButtonCode, const EInputKeyType Type = EInputKeyType::KeyboardButton) : Type(Type), ButtonCode(ButtonCode) {}
	explicit FInputKey(const EInputAxisOrientation AxisOrientation) : Type(EInputKeyType::MouseAxis1D), AxisOrientation(AxisOrientation) {}

	// Gamepad Button
	explicit FInputKey(const SDL_GamepadButton GamepadButton) : Type(EInputKeyType::GamepadButton), GamepadButton(GamepadButton) {}

	// Gamepad Axis
	explicit FInputKey(const SDL_GamepadAxis GamepadAxis, const EInputKeyType Type) : Type(Type), GamepadAxis(GamepadAxis) {}
	explicit FInputKey(const FInputGamepadAxisPair GamepadAxisPair, const EInputKeyType Type) : Type(Type), GamepadAxisPair(GamepadAxisPair) {}

	bool IsValid() const { return Type == EInputKeyType::Unknown; }

	bool operator==(const FInputKey& Other) const
	{
		if (Type != Other.Type)
		{
			return false;
		}

		switch (Type)
		{
		case EInputKeyType::KeyboardButton:
		case EInputKeyType::MouseButton:
			return ButtonCode == Other.ButtonCode;

		case EInputKeyType::MouseAxis1D:
			return AxisOrientation == Other.AxisOrientation;

		case EInputKeyType::MouseAxis2D:
			return true;

		case EInputKeyType::GamepadButton:
			return GamepadButton == Other.GamepadButton;

		case EInputKeyType::GamepadTriggerAxis:
		case EInputKeyType::GamepadJoystickAxis1D:
			return GamepadAxis == Other.GamepadAxis;

		case EInputKeyType::GamepadJoystickAxis2D:
			return GamepadAxisPair == Other.GamepadAxisPair;

		case EInputKeyType::Unknown:
			return true;

		default:
			return false;
		}
	}

	bool operator!=(const FInputKey& Other) const
	{
		return !(*this == Other);
	}

	FString ToString() const
	{
		switch (Type)
		{
		case EInputKeyType::KeyboardButton:
			return "Keyboard_" + FString(SDL_GetKeyName(ButtonCode));

		case EInputKeyType::MouseButton:
			switch (ButtonCode)
			{
			case SDL_BUTTON_LEFT:
				return "Mouse_Left";

			case SDL_BUTTON_RIGHT:
				return "Mouse_Right";

			case SDL_BUTTON_MIDDLE:
				return "Mouse_Middle";

			case SDL_BUTTON_X1:
				return "Mouse_Thumb1";

			case SDL_BUTTON_X2:
				return "Mouse_Thumb2";

			default:
				return "Mouse_Unknown";
			}

		case EInputKeyType::MouseAxis1D:
			switch (AxisOrientation)
			{
			case EInputAxisOrientation::X:
				return "MouseAxis1D_X";

			case EInputAxisOrientation::Y:
				return "MouseAxis1D_Y";

			case EInputAxisOrientation::Unknown:
			default:
				return "MouseAxis1D_Unknown";
			}

		case EInputKeyType::MouseAxis2D:
			return "MouseAxis2D_XY";

		case EInputKeyType::GamepadButton:
			return "GamepadButton_" + FString(SDL_GetGamepadStringForButton(GamepadButton));

		case EInputKeyType::GamepadTriggerAxis:
			return "GamepadTriggerAxis_" + FString(SDL_GetGamepadStringForAxis(GamepadAxis));

		case EInputKeyType::GamepadJoystickAxis1D:
			return "GamepadJoystickAxis1D_" + FString(SDL_GetGamepadStringForAxis(GamepadAxis));

		case EInputKeyType::GamepadJoystickAxis2D:
			{
				FString AxisString = SDL_GetGamepadStringForAxis(GamepadAxis);
				AxisString.RemoveChars(1);
				return "GamepadJoystickAxis2D_" + AxisString + "XY";
			}

		case EInputKeyType::Unknown:
		default:
			return "Unknown";
		}
	}
};

namespace std
{
template <>
struct hash<FInputGamepadAxisPair>
{
	size_t operator()(const FInputGamepadAxisPair& GamepadAxisPair) const noexcept
	{
		size_t h1 = std::hash<int>{}(GamepadAxisPair.Horizontal);
		size_t h2 = std::hash<int>{}(GamepadAxisPair.Vertical);

		return h1 ^ (h2 << 1);
	}
};

template <>
struct hash<FInputKey>
{
	size_t operator()(const FInputKey& InputKey) const noexcept
	{
		size_t h1 = std::hash<Uint8>{}(static_cast<Uint8>(InputKey.Type));
		size_t h2;

		// Hash the specific value based on type
		switch (InputKey.Type)
		{
		case EInputKeyType::KeyboardButton:
		case EInputKeyType::MouseButton:
			h2 = std::hash<int>{}(static_cast<int>(InputKey.ButtonCode));
			break;

		case EInputKeyType::MouseAxis1D:
			h2 = std::hash<int>{}(static_cast<int>(InputKey.AxisOrientation));
			break;

		case EInputKeyType::MouseAxis2D:
			return h1;

		case EInputKeyType::GamepadButton:
			h2 = std::hash<int>{}(InputKey.GamepadButton);
			break;

		case EInputKeyType::GamepadTriggerAxis:
		case EInputKeyType::GamepadJoystickAxis1D:
			h2 = std::hash<int>{}(InputKey.GamepadAxis);
			break;

		case EInputKeyType::GamepadJoystickAxis2D:
			h2 = std::hash<FInputGamepadAxisPair>{}(InputKey.GamepadAxisPair);
			break;

		case EInputKeyType::Unknown:
		default:
			h2 = std::hash<int>{}(InputKey.RawValue); // Hash the raw value for unknown
			break;
		}
		// Combine hashes. A common way is using boost::hash_combine or similar
		// Simple XOR or sum can lead to collisions, but good enough for a start
		return h1 ^ (h2 << 1); // Simple hash combine
	}
};
}

namespace EInputKeys
{
// --- Keyboard Keys ---
// Alphabet
const FInputKey A(SDLK_A);
const FInputKey B(SDLK_B);
const FInputKey C(SDLK_C);
const FInputKey D(SDLK_D);
const FInputKey E(SDLK_E);
const FInputKey F(SDLK_F);
const FInputKey G(SDLK_G);
const FInputKey H(SDLK_H);
const FInputKey I(SDLK_I);
const FInputKey J(SDLK_J);
const FInputKey K(SDLK_K);
const FInputKey L(SDLK_L);
const FInputKey M(SDLK_M);
const FInputKey N(SDLK_N);
const FInputKey O(SDLK_O);
const FInputKey P(SDLK_P);
const FInputKey Q(SDLK_Q);
const FInputKey R(SDLK_R);
const FInputKey S(SDLK_S);
const FInputKey T(SDLK_T);
const FInputKey U(SDLK_U);
const FInputKey V(SDLK_V);
const FInputKey W(SDLK_W);
const FInputKey X(SDLK_X);
const FInputKey Y(SDLK_Y);
const FInputKey Z(SDLK_Z);

// Numbers
const FInputKey Zero(SDLK_0);
const FInputKey One(SDLK_1);
const FInputKey Two(SDLK_2);
const FInputKey Three(SDLK_3);
const FInputKey Four(SDLK_4);
const FInputKey Five(SDLK_5);
const FInputKey Six(SDLK_6);
const FInputKey Seven(SDLK_7);
const FInputKey Eight(SDLK_8);
const FInputKey Nine(SDLK_9);

// Special Keys
const FInputKey Escape(SDLK_ESCAPE);
const FInputKey Spacebar(SDLK_SPACE);
const FInputKey Enter(SDLK_RETURN);
const FInputKey Tab(SDLK_TAB);
const FInputKey Backspace(SDLK_BACKSPACE);
const FInputKey Delete(SDLK_DELETE);
const FInputKey RightShift(SDLK_RSHIFT);
const FInputKey LeftShift(SDLK_LSHIFT);
const FInputKey RightCtrl(SDLK_RCTRL);
const FInputKey LeftCtrl(SDLK_LCTRL);
const FInputKey RightAlt(SDLK_RALT);
const FInputKey LeftAlt(SDLK_LALT);
const FInputKey RightGUI(SDLK_RGUI); // Windows key, Command key
const FInputKey LeftGUI(SDLK_LGUI);  // Windows key, Command key

// Arrow Keys
const FInputKey Up(SDLK_UP);
const FInputKey Down(SDLK_DOWN);
const FInputKey Left(SDLK_LEFT);
const FInputKey Right(SDLK_RIGHT);

// Function Keys
const FInputKey F1(SDLK_F1);
const FInputKey F2(SDLK_F2);
const FInputKey F3(SDLK_F3);
const FInputKey F4(SDLK_F4);
const FInputKey F5(SDLK_F5);
const FInputKey F6(SDLK_F6);
const FInputKey F7(SDLK_F7);
const FInputKey F8(SDLK_F8);
const FInputKey F9(SDLK_F9);
const FInputKey F10(SDLK_F10);
const FInputKey F11(SDLK_F11);
const FInputKey F12(SDLK_F12);

// --- Mouse Buttons ---
const FInputKey MouseLeft(SDL_BUTTON_LEFT, EInputKeyType::MouseButton);
const FInputKey MouseRight(SDL_BUTTON_RIGHT, EInputKeyType::MouseButton);
const FInputKey MouseMiddle(SDL_BUTTON_MIDDLE, EInputKeyType::MouseButton);
const FInputKey MouseX1(SDL_BUTTON_X1, EInputKeyType::MouseButton); // Side button 1
const FInputKey MouseX2(SDL_BUTTON_X2, EInputKeyType::MouseButton); // Side button 2

// --- Mouse Axes ---
const FInputKey MouseX(EInputAxisOrientation::X);
const FInputKey MouseY(EInputAxisOrientation::Y);
const FInputKey MouseXY(EInputKeyType::MouseAxis2D);

// --- Gamepad Buttons (based on standard layout) ---
const FInputKey GamepadFaceButtonBottom(SDL_GAMEPAD_BUTTON_SOUTH); // A on Xbox, Cross on PlayStation, B on Switch
const FInputKey GamepadFaceButtonRight(SDL_GAMEPAD_BUTTON_EAST);   // B on Xbox, Circle on PlayStation, A on Switch
const FInputKey GamepadFaceButtonLeft(SDL_GAMEPAD_BUTTON_WEST);    // X on Xbox, Square on PlayStation, Y on Switch
const FInputKey GamepadFaceButtonTop(SDL_GAMEPAD_BUTTON_NORTH);    // Y on Xbox, Triangle on PlayStation, X on Switch

const FInputKey GamepadDPadUp(SDL_GAMEPAD_BUTTON_DPAD_UP);
const FInputKey GamepadDPadDown(SDL_GAMEPAD_BUTTON_DPAD_DOWN);
const FInputKey GamepadDPadLeft(SDL_GAMEPAD_BUTTON_DPAD_LEFT);
const FInputKey GamepadDPadRight(SDL_GAMEPAD_BUTTON_DPAD_RIGHT);

const FInputKey GamepadLeftShoulder(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
const FInputKey GamepadRightShoulder(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);

const FInputKey GamepadLeftThumbstick(SDL_GAMEPAD_BUTTON_LEFT_STICK);
const FInputKey GamepadRightThumbstick(SDL_GAMEPAD_BUTTON_RIGHT_STICK);

const FInputKey GamepadStart(SDL_GAMEPAD_BUTTON_START);
const FInputKey GamepadBack(SDL_GAMEPAD_BUTTON_BACK);
const FInputKey GamepadGuide(SDL_GAMEPAD_BUTTON_GUIDE); // Xbox button, PS button, Home on Switch

const FInputKey GamepadMisc1(SDL_GAMEPAD_BUTTON_MISC1); // Share button on Xbox Series X, Mic on PS5, Capture on Switch

const FInputKey GamepadRightPaddle1(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1);
const FInputKey GamepadLeftPaddle1(SDL_GAMEPAD_BUTTON_LEFT_PADDLE1);
const FInputKey GamepadRightPaddle2(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2);
const FInputKey GamepadLeftPaddle2(SDL_GAMEPAD_BUTTON_LEFT_PADDLE2);
const FInputKey GamepadTouchpad(SDL_GAMEPAD_BUTTON_TOUCHPAD);

// --- Gamepad Axes ---
const FInputKey GamepadLeftX(SDL_GAMEPAD_AXIS_LEFTX, EInputKeyType::GamepadJoystickAxis1D);
const FInputKey GamepadLeftY(SDL_GAMEPAD_AXIS_LEFTY, EInputKeyType::GamepadJoystickAxis1D);
const FInputKey GamepadLeftXY(FInputGamepadAxisPair(SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY), EInputKeyType::GamepadJoystickAxis2D);
const FInputKey GamepadRightX(SDL_GAMEPAD_AXIS_RIGHTX, EInputKeyType::GamepadJoystickAxis1D);
const FInputKey GamepadRightY(SDL_GAMEPAD_AXIS_RIGHTY, EInputKeyType::GamepadJoystickAxis1D);
const FInputKey GamepadRightXY(FInputGamepadAxisPair(SDL_GAMEPAD_AXIS_RIGHTX, SDL_GAMEPAD_AXIS_RIGHTY), EInputKeyType::GamepadJoystickAxis2D);

const FInputKey GamepadLeftTriggerAxis(SDL_GAMEPAD_AXIS_LEFT_TRIGGER, EInputKeyType::GamepadTriggerAxis);
const FInputKey GamepadRightTriggerAxis(SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, EInputKeyType::GamepadTriggerAxis);
}
