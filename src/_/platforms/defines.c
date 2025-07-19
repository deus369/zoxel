#if defined(__ANDROID__)

    #define zoxel_on_android

    // custom defines for android
    // #define zox_disable_post_processing

#elif defined(__EMSCRIPTEN__)

    #define zoxel_on_web

    // custom defines for web
    #define zox_disable_module_networking
    // #define zox_disable_terrain_textures // this kinda breaks
    #define zox_disable_render_element3D
    #define zox_disable_post_processing

#elif defined(_WIN32)
    #define zoxel_on_windows
#else
    #define zoxel_on_linux
#endif
#if defined(STEAMDECK)
    #define zoxel_on_steamdeck
#endif

// for now web has to disable characters
#ifdef zoxel_on_web
    #define zox_disable_npcs
#endif
