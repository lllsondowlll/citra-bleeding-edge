// Copyright 2017 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <string>
#include "input_common/keyboard.h"

namespace InputCommon {

/// Initializes and registers all built-in input device factories.
void Init();

/// Unresisters all build-in input device factories and shut them down.
void Shutdown();

/// Gets the keyboard button device factory.
Keyboard* GetKeyboard();

/// Generates a serialized param package for creating a keyboard button device
std::string GenerateKeyboardParam(int key_code);

/// Generates a serialized param package for creating an analog device taking input from keyboard
std::string GenerateAnalogParamFromKeys(int key_up, int key_down, int key_left, int key_right,
                                        int key_modifier, float modifier_scale);

} // namespace InputCommon