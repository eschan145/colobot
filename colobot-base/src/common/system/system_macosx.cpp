/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2023, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

#include "common/system/system_macosx.h"

#include "common/logger.h"
#include "common/stringutils.h"
#include "common/version.h"

#include <stdlib.h>
#include <unistd.h>

// MacOS-specific headers
#include <CoreFoundation/CFBundle.h>
#include <CoreServices/CoreServices.h>

#include <filesystem>

inline std::string CFStringRefToStdString(CFStringRef str) {

    std::string stdstr;

    char *fullPath;
    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();

    // 1st try for English system
    fullPath = const_cast<char*>(CFStringGetCStringPtr(str, encodingMethod));
    if( fullPath == nullptr )
    {
        // 2nd try for Japanese system
        encodingMethod = kCFStringEncodingUTF8;
        fullPath = const_cast<char*>(CFStringGetCStringPtr(str, encodingMethod));
    }

    // for safer operation.
    if( fullPath == nullptr )
    {
        CFIndex length = CFStringGetLength(str);
        fullPath = static_cast<char *>(malloc( length + 1 ));

        // TODO: Check boolean result of that conversion
        CFStringGetCString(str, fullPath, length, kCFStringEncodingUTF8 );

        stdstr = fullPath;

        free( fullPath );
    }
    else
        stdstr = fullPath;

    return stdstr;
}

std::unique_ptr<CSystemUtils> CSystemUtils::Create()
{
    return std::make_unique<CSystemUtilsMacOSX>();
}

void CSystemUtilsMacOSX::Init(const std::vector<std::string>& args)
{
    m_arguments = args;

    // These functions are a deprecated way to get the 'Application Support' folder, but they do work, in plain C++
    FSRef ref;
    OSType folderType = kApplicationSupportFolderType;
    char path[PATH_MAX];
    FSFindFolder( kUserDomain, folderType, kCreateFolder, &ref );
    FSRefMakePath( &ref, reinterpret_cast<UInt8*>(&path), PATH_MAX );

    m_ASPath = StrUtils::ToPath(path) / "colobot";

    // Make sure the directory exists
    std::filesystem::create_directories(m_ASPath);

    // Get the Resources bundle URL
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
    CFRelease(resourcesURL);

    m_dataPath = StrUtils::ToPath(CFStringRefToStdString(str));
    m_dataPath /= "Contents/Resources";
}

SystemDialogResult CSystemUtilsMacOSX::SystemDialog(SystemDialogType type, const std::string& title, const std::string& message)
{
    return ConsoleSystemDialog(type, title, message);
}

std::filesystem::path CSystemUtilsMacOSX::GetDataPath() const
{
    return m_dataPath;
}

std::filesystem::path CSystemUtilsMacOSX::GetLangPath() const
{
    return m_dataPath / "i18n";
}

std::filesystem::path CSystemUtilsMacOSX::GetSaveDir() const
{
    if constexpr (Version::PORTABLE_SAVES || Version::DEVELOPMENT_BUILD)
    {
        // TODO: I have no idea if this actually works on Mac OS
        return "./saves";
    }
    else
    {
        std::filesystem::path savegameDir = m_ASPath;
        GetLogger()->Trace("Saved game files are going to %%", savegameDir);

        return savegameDir;
    }
}

std::string CSystemUtilsMacOSX::GetEnvVar(const std::string& str) const
{
    // TODO: I have no Mac
    return std::string();
}

bool CSystemUtilsMacOSX::OpenPath(const std::filesystem::path& path)
{
    int result = system(("open \"" + StrUtils::ToString(path) + "\"").c_str()); // TODO: Test on macOS
    if (result != 0)
    {
        GetLogger()->Error("Failed to open path: %%, error code: %%", path, result);
        return false;
    }
    return true;
}

bool CSystemUtilsMacOSX::OpenWebsite(const std::string& url)
{
    int result = system(("open \"" + url + "\"").c_str()); // TODO: Test on macOS
    if (result != 0)
    {
        GetLogger()->Error("Failed to open url: %%, error code: %%", url, result);
        return false;
    }
    return true;
}
