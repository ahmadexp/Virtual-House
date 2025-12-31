#ifndef _PLATFORM_AUDIO_H_
#define _PLATFORM_AUDIO_H_

// Platform-specific audio support

#ifdef _WIN32
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

// Windows PlaySound wrapper
inline void PlatformPlaySound(const char* filename, bool async) {
    PlaySound((LPCSTR)filename, NULL, SND_FILENAME | (async ? SND_ASYNC : SND_SYNC));
}

#elif defined(__APPLE__)
#include <AudioToolbox/AudioToolbox.h>
#include <string>

// macOS audio playback using AudioToolbox
inline void PlatformPlaySound(const char* filename, bool async) {
    // Simple implementation using system command as fallback
    // For production, use AudioToolbox API properly
    std::string cmd = "afplay \"";
    
    cmd += filename;
    cmd += "\"";
    
    if (async) {
        cmd += " > /dev/null 2>&1 &";
    }
    
    system(cmd.c_str());
}

#elif defined(__linux__)
#include <cstdlib>
#include <string>

// Linux audio playback using aplay/paplay
inline void PlatformPlaySound(const char* filename, bool async) {
    std::string cmd = "aplay ";
    cmd += filename;
    if (async) {
        cmd += " &";
    }
    system(cmd.c_str());
}

#else
// Fallback: no sound
inline void PlatformPlaySound(const char* filename, bool async) {
    // No-op
}
#endif

#endif // _PLATFORM_AUDIO_H_
