#pragma once

#include <string_view>

namespace Version
{
    inline constexpr bool OFFICIAL_BUILD = @CONFIG_OFFICIAL_BUILD@;
    inline constexpr bool DEVELOPMENT_BUILD = @CONFIG_DEVELOPMENT_BUILD@;
    inline constexpr bool PORTABLE_SAVES = @CONFIG_PORTABLE_SAVES@;
    inline constexpr bool RELATIVE_PATHS = @CONFIG_RELATIVE_PATHS@;

    inline constexpr int BUILD_NUMBER = @BUILD_NUMBER@;

    inline constexpr std::string_view FULL_NAME = "Colobot: Gold Edition @COLOBOT_VERSION_FULL@";
    inline constexpr std::string_view VERSION = "@CMAKE_PROJECT_VERSION@";
    inline constexpr int MAJOR = @CMAKE_PROJECT_VERSION_MAJOR@;
    inline constexpr int MINOR = @CMAKE_PROJECT_VERSION_MINOR@;
    inline constexpr int PATCH = @CMAKE_PROJECT_VERSION_PATCH@;
    inline constexpr std::string_view VERSION_DISPLAY = "@COLOBOT_VERSION_DISPLAY@";
}
