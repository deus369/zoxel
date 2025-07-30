#if defined(__EMSCRIPTEN__)

    #define zox_web

    // custom defines for web
    #define zox_disable_module_networking
    // #define zox_disable_terrain_textures // this kinda breaks
    #define zox_disable_render_element3D
    #define zox_disable_post_processing

#endif

#if defined(STEAMDECK)
    #define zoxel_on_steamdeck
#endif