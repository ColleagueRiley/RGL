/*	NSPathUtilities.h
	Copyright (c) 1994-2019, Apple Inc. All rights reserved.
*/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "../../macros.h"
#include "../types.h"


typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
    NSApplicationDirectory = 1,             // supported applications (Applications)
    NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
    NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
    NSAdminApplicationDirectory,            // system and network administration applications (Administration)
    NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
    NSUserDirectory,                        // user home directories (Users)
    NSDocumentationDirectory,               // documentation (Documentation)
    NSDocumentDirectory,                    // documents (Documents)
    NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
    NSAutosavedInformationDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 11,   // location of autosaved documents (Documents/Autosaved)
    NSDesktopDirectory = 12,                // location of user's desktop
    NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
    NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
    NSDownloadsDirectory API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0)) = 15,              // location of the user's "Downloads" directory
    NSInputMethodsDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 16,           // input methods (Library/Input Methods)
    NSMoviesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 17,                 // location of user's Movies directory (~/Movies)
    NSMusicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 18,                  // location of user's Music directory (~/Music)
    NSPicturesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 19,               // location of user's Pictures directory (~/Pictures)
    NSPrinterDescriptionDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
    NSSharedPublicDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 21,           // location of user's Public sharing directory (~/Public)
    NSPreferencePanesDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
    NSApplicationScriptsDirectory API_AVAILABLE(macos(10.8)) API_UNAVAILABLE(ios, watchos, tvos) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
    NSItemReplacementDirectory API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0)) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
    NSAllApplicationsDirectory = 100,       // all directories where applications can occur
    NSAllLibrariesDirectory = 101,          // all directories where resources can occur
    NSTrashDirectory API_AVAILABLE(macos(10.8), ios(11.0)) API_UNAVAILABLE(watchos, tvos) = 102             // location of Trash directory

};

typedef NS_OPTIONS(NSUInteger, NSSearchPathDomainMask) {
    NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
    NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
    NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};


#ifdef __cplusplus
}
#endif