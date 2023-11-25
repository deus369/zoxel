#if defined(__ANDROID__)
    #define zoxel_on_android
#elif defined(__EMSCRIPTEN__)
    #define zoxel_on_web
#elif defined(_WIN32)
    #define zoxel_on_windows
#else
    #define zoxel_on_linux
#endif
#if defined(STEAMDECK)
    #define zoxel_on_steamdeck
#endif
