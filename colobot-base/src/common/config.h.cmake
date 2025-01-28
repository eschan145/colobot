#pragma once

#include <string_view>

// Macros set by CMake
#cmakedefine PLATFORM_MACOSX @PLATFORM_MACOSX@

#ifdef PLATFORM_MACOSX
// Assume we have the Mac OS X function CFLocaleCopyCurrent in the CoreFoundation framework
#define HAVE_CFLOCALECOPYCURRENT 1
#endif

#cmakedefine OPENAL_SOUND

namespace Config
{

// Default data directory
inline constexpr std::string_view DATA_DIR = "@COLOBOT_DATA_DIR@";
// Default language directory
inline constexpr std::string_view LANG_DIR = "@COLOBOT_I18N_DIR@";

}
