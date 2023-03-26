#if defined(__unix__) && __ANDROID__
    #define ANDROID_BUILD
#endif
#ifdef __EMSCRIPTEN__
    #define WEB_BUILD
#endif
#ifdef _WIN32
    #define WINDOWS_BUILD
#endif