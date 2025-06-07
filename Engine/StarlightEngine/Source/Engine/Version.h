// Copyright © 2025 Bman, Inc. All rights reserved.

#pragma once

#include <string>

class StarlightEngineVersion
{
public:
    static constexpr int MAJOR = 1;
    static constexpr int MINOR = 0;
    static constexpr int PATCH = 0;

    static inline std::string GetVersionString()
    {
        return std::to_string(MAJOR) + "." + std::to_string(MINOR) + "." + std::to_string(PATCH);
    }
};
