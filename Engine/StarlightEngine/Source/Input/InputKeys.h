// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

// Libraries
#include <SDL3/SDL_keycode.h>

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

struct SInputGamepadAxisPair
{
	SDL_GamepadAxis Horizontal;
	SDL_GamepadAxis Vertical;

	explicit SInputGamepadAxisPair(const SDL_GamepadAxis Horizontal, const SDL_GamepadAxis Vertical) : Horizontal(Horizontal), Vertical(Vertical) {}

	bool operator==(const SInputGamepadAxisPair& Other) const
	{
		return Horizontal == Other.Horizontal && Vertical == Other.Vertical;
	}

	bool operator!=(const SInputGamepadAxisPair& Other) const
	{
		return !(*this == Other);
	}
};

struct SInputKey
{
	EInputKeyType Type;

	// Identifier from type
	union
	{
		Uint32 ButtonCode;
		EInputAxisOrientation AxisOrientation;
		SDL_GamepadButton GamepadButton;
		SDL_GamepadAxis GamepadAxis;
		SInputGamepadAxisPair GamepadAxisPair;
		int RawValue;
	};

	// Default Constructor
	SInputKey() : Type(EInputKeyType::Unknown), RawValue(0) {}

	// General
	explicit SInputKey(const EInputKeyType Type) : Type(Type), RawValue(0) {}

	// Keyboard / Mouse Button
	explicit SInputKey(const Uint32 ButtonCode, const EInputKeyType Type = EInputKeyType::KeyboardButton) : Type(Type), ButtonCode(ButtonCode) {}
	explicit SInputKey(const EInputAxisOrientation AxisOrientation) : Type(EInputKeyType::MouseAxis1D), AxisOrientation(AxisOrientation) {}

	// Gamepad Button
	explicit SInputKey(const SDL_GamepadButton GamepadButton) : Type(EInputKeyType::GamepadButton), GamepadButton(GamepadButton) {}

	// Gamepad Axis
	explicit SInputKey(const SDL_GamepadAxis GamepadAxis, const EInputKeyType Type) : Type(Type), GamepadAxis(GamepadAxis) {}
	explicit SInputKey(const SInputGamepadAxisPair GamepadAxisPair, const EInputKeyType Type) : Type(Type), GamepadAxisPair(GamepadAxisPair) {}

	bool IsValid() const { return Type == EInputKeyType::Unknown; }

	bool operator==(const SInputKey& Other) const
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

	bool operator!=(const SInputKey& Other) const
	{
		return !(*this == Other);
	}

	std::string ToString() const
	{
		switch (Type)
		{
		case EInputKeyType::KeyboardButton:
			return "Keyboard_" + std::string(SDL_GetKeyName(ButtonCode));

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
			return "GamepadButton_" + std::string(SDL_GetGamepadStringForButton(GamepadButton));

		case EInputKeyType::GamepadTriggerAxis:
			return "GamepadTriggerAxis_" + std::string(SDL_GetGamepadStringForAxis(GamepadAxis));

		case EInputKeyType::GamepadJoystickAxis1D:
			return "GamepadJoystickAxis1D_" + std::string(SDL_GetGamepadStringForAxis(GamepadAxis));

		case EInputKeyType::GamepadJoystickAxis2D:
			{
				std::string AxisString = SDL_GetGamepadStringForAxis(GamepadAxis);
				AxisString.pop_back();
				return "GamepadJoystickAxis2D_" + AxisString + "XY";
			}

		default:
			return "Unknown";
		}
	}
};

namespace std
{
template <>
struct hash<SInputGamepadAxisPair>
{
	size_t operator()(const SInputGamepadAxisPair& GamepadAxisPair) const
	{
		size_t h1 = std::hash<int>{}(GamepadAxisPair.Horizontal);
		size_t h2 = std::hash<int>{}(GamepadAxisPair.Vertical);

		return h1 ^ (h2 << 1);
	}
};

template <>
struct hash<SInputKey>
{
	size_t operator()(const SInputKey& InputKey) const
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
			h2 = std::hash<SInputGamepadAxisPair>{}(InputKey.GamepadAxisPair);
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
const SInputKey A(SDLK_A);
const SInputKey B(SDLK_B);
const SInputKey C(SDLK_C);
const SInputKey D(SDLK_D);
const SInputKey E(SDLK_E);
const SInputKey F(SDLK_F);
const SInputKey G(SDLK_G);
const SInputKey H(SDLK_H);
const SInputKey I(SDLK_I);
const SInputKey J(SDLK_J);
const SInputKey K(SDLK_K);
const SInputKey L(SDLK_L);
const SInputKey M(SDLK_M);
const SInputKey N(SDLK_N);
const SInputKey O(SDLK_O);
const SInputKey P(SDLK_P);
const SInputKey Q(SDLK_Q);
const SInputKey R(SDLK_R);
const SInputKey S(SDLK_S);
const SInputKey T(SDLK_T);
const SInputKey U(SDLK_U);
const SInputKey V(SDLK_V);
const SInputKey W(SDLK_W);
const SInputKey X(SDLK_X);
const SInputKey Y(SDLK_Y);
const SInputKey Z(SDLK_Z);

// Numbers
const SInputKey Zero(SDLK_0);
const SInputKey One(SDLK_1);
const SInputKey Two(SDLK_2);
const SInputKey Three(SDLK_3);
const SInputKey Four(SDLK_4);
const SInputKey Five(SDLK_5);
const SInputKey Six(SDLK_6);
const SInputKey Seven(SDLK_7);
const SInputKey Eight(SDLK_8);
const SInputKey Nine(SDLK_9);

// Special Keys
const SInputKey Escape(SDLK_ESCAPE);
const SInputKey Spacebar(SDLK_SPACE);
const SInputKey Enter(SDLK_RETURN);
const SInputKey Tab(SDLK_TAB);
const SInputKey Backspace(SDLK_BACKSPACE);
const SInputKey Delete(SDLK_DELETE);
const SInputKey RightShift(SDLK_RSHIFT);
const SInputKey LeftShift(SDLK_LSHIFT);
const SInputKey RightCtrl(SDLK_RCTRL);
const SInputKey LeftCtrl(SDLK_LCTRL);
const SInputKey RightAlt(SDLK_RALT);
const SInputKey LeftAlt(SDLK_LALT);
const SInputKey RightGUI(SDLK_RGUI); // Windows key, Command key
const SInputKey LeftGUI(SDLK_LGUI);  // Windows key, Command key

// Arrow Keys
const SInputKey Up(SDLK_UP);
const SInputKey Down(SDLK_DOWN);
const SInputKey Left(SDLK_LEFT);
const SInputKey Right(SDLK_RIGHT);

// Function Keys
const SInputKey F1(SDLK_F1);
const SInputKey F2(SDLK_F2);
const SInputKey F3(SDLK_F3);
const SInputKey F4(SDLK_F4);
const SInputKey F5(SDLK_F5);
const SInputKey F6(SDLK_F6);
const SInputKey F7(SDLK_F7);
const SInputKey F8(SDLK_F8);
const SInputKey F9(SDLK_F9);
const SInputKey F10(SDLK_F10);
const SInputKey F11(SDLK_F11);
const SInputKey F12(SDLK_F12);

// --- Mouse Buttons ---
const SInputKey MouseLeft(SDL_BUTTON_LEFT, EInputKeyType::MouseButton);
const SInputKey MouseRight(SDL_BUTTON_RIGHT, EInputKeyType::MouseButton);
const SInputKey MouseMiddle(SDL_BUTTON_MIDDLE, EInputKeyType::MouseButton);
const SInputKey MouseX1(SDL_BUTTON_X1, EInputKeyType::MouseButton); // Side button 1
const SInputKey MouseX2(SDL_BUTTON_X2, EInputKeyType::MouseButton); // Side button 2

// --- Mouse Axes ---
const SInputKey MouseX(EInputAxisOrientation::X);
const SInputKey MouseY(EInputAxisOrientation::Y);
const SInputKey MouseXY(EInputKeyType::MouseAxis2D);

// --- Gamepad Buttons (based on standard layout) ---
const SInputKey GamepadFaceButtonBottom(SDL_GAMEPAD_BUTTON_SOUTH); // A on Xbox, Cross on PlayStation, B on Switch
const SInputKey GamepadFaceButtonRight(SDL_GAMEPAD_BUTTON_EAST);   // B on Xbox, Circle on PlayStation, A on Switch
const SInputKey GamepadFaceButtonLeft(SDL_GAMEPAD_BUTTON_WEST);    // X on Xbox, Square on PlayStation, Y on Switch
const SInputKey GamepadFaceButtonTop(SDL_GAMEPAD_BUTTON_NORTH);    // Y on Xbox, Triangle on PlayStation, X on Switch

const SInputKey GamepadDPadUp(SDL_GAMEPAD_BUTTON_DPAD_UP);
const SInputKey GamepadDPadDown(SDL_GAMEPAD_BUTTON_DPAD_DOWN);
const SInputKey GamepadDPadLeft(SDL_GAMEPAD_BUTTON_DPAD_LEFT);
const SInputKey GamepadDPadRight(SDL_GAMEPAD_BUTTON_DPAD_RIGHT);

const SInputKey GamepadLeftShoulder(SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
const SInputKey GamepadRightShoulder(SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);

const SInputKey GamepadLeftThumbstick(SDL_GAMEPAD_BUTTON_LEFT_STICK);
const SInputKey GamepadRightThumbstick(SDL_GAMEPAD_BUTTON_RIGHT_STICK);

const SInputKey GamepadStart(SDL_GAMEPAD_BUTTON_START);
const SInputKey GamepadBack(SDL_GAMEPAD_BUTTON_BACK);
const SInputKey GamepadGuide(SDL_GAMEPAD_BUTTON_GUIDE); // Xbox button, PS button, Home on Switch

const SInputKey GamepadMisc1(SDL_GAMEPAD_BUTTON_MISC1); // Share button on Xbox Series X, Mic on PS5, Capture on Switch

const SInputKey GamepadRightPaddle1(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1);
const SInputKey GamepadLeftPaddle1(SDL_GAMEPAD_BUTTON_LEFT_PADDLE1);
const SInputKey GamepadRightPaddle2(SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2);
const SInputKey GamepadLeftPaddle2(SDL_GAMEPAD_BUTTON_LEFT_PADDLE2);
const SInputKey GamepadTouchpad(SDL_GAMEPAD_BUTTON_TOUCHPAD);

// --- Gamepad Axes ---
const SInputKey GamepadLeftX(SDL_GAMEPAD_AXIS_LEFTX, EInputKeyType::GamepadJoystickAxis1D);
const SInputKey GamepadLeftY(SDL_GAMEPAD_AXIS_LEFTY, EInputKeyType::GamepadJoystickAxis1D);
const SInputKey GamepadLeftXY(SInputGamepadAxisPair(SDL_GAMEPAD_AXIS_LEFTX, SDL_GAMEPAD_AXIS_LEFTY), EInputKeyType::GamepadJoystickAxis2D);
const SInputKey GamepadRightX(SDL_GAMEPAD_AXIS_RIGHTX, EInputKeyType::GamepadJoystickAxis1D);
const SInputKey GamepadRightY(SDL_GAMEPAD_AXIS_RIGHTY, EInputKeyType::GamepadJoystickAxis1D);
const SInputKey GamepadRightXY(SInputGamepadAxisPair(SDL_GAMEPAD_AXIS_RIGHTX, SDL_GAMEPAD_AXIS_RIGHTY), EInputKeyType::GamepadJoystickAxis2D);

const SInputKey GamepadLeftTriggerAxis(SDL_GAMEPAD_AXIS_LEFT_TRIGGER, EInputKeyType::GamepadTriggerAxis);
const SInputKey GamepadRightTriggerAxis(SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, EInputKeyType::GamepadTriggerAxis);
}
