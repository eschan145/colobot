#pragma once

#include <string_view>

namespace Version
{
    static inline constexpr bool OFFICIAL_BUILD = false;
    static inline constexpr bool DEVELOPMENT_BUILD = false;
    static inline constexpr bool PORTABLE_SAVES = false;
    static inline constexpr bool RELATIVE_PATHS = false;

    static inline constexpr int BUILD_NUMBER = 0;

    static inline constexpr std::string_view FULL_NAME = "Colobot: Gold Edition 0.2.1.0+alpha-git-master~r02bdd9d8";
    static inline constexpr std::string_view VERSION = "0.2.1.0";
    static inline constexpr int MAJOR = 0;
    static inline constexpr int MINOR = 2;
    static inline constexpr int PATCH = 1;
    static inline constexpr std::string_view VERSION_DISPLAY = "git-master~r02bdd9d8";
}
