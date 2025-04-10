// disables
// #define zox_disable_post_processing

// #define zox_is_flatlands

// lags on weaker cpus
// #define zox_disable_music
// lag spikes during chunks

// #define zoxel_mouse_emulate_touch
// #define zoxel_start_with_debug_ui
// still testing this
// #define zox_disable_touch_buttons

// if android, this shouldn't need to be here?
#ifdef __ANDROID__
    #ifndef zox_lib_sdl
        #define zox_lib_sdl
    #endif
    #ifndef zox_lib_sdl_images
        #define zox_lib_sdl_images
    #endif
    #ifndef zox_lib_sdl_mixer
        #define zox_lib_sdl_mixer
    #endif
#endif

// #define zox_disable_tilemaps
// #define zox_log_realm_generate


// #define zox_disable_player_ui

// #define zox_disable_save_games
// #define zox_disable_player_character
/*#define zox_disable_io_textures
#define zox_disable_io_voxes*/

// #define zox_disable_skybox
// #define zox_test_settings_00
// #define zox_is_flatlands

// #define zox_disable_module_networking

// #define zox_disable_canvas_overlay

// #define zoxel_catch_opengl_errors

// #define zox_disable_depth_buffer
// #define zox_disable_render_texture

// #define zox_disable_terrain_lod_levels

// #define zox_test_settings_01
// #define zox_test_settings_02
// #define zox_test_settings_03

// boot disables
// #define zox_disable_frustum_checks
// #define zox_disable_skybox
// #define zox_disable_main_menu


// #define zox_disable_io
// #define zox_disable_audio

// #define zox_disable_play_sounds

#define zox_disable_mouse_constraint
#define zox_disable_gamepad_stick_as_any_input // used for samsung phone, it's buggy af
#define zox_disable_gamepad_deadzones
// #define zoxel_disable_gamepads

// #define zox_disable_set_vox
// #define zox_extra_destroy_terrain_children
// this seems to create more triangles and not dispose them properly
// #define zox_disable_terrain_streaming
// #define zox_disable_chunk_linking
// #define zox_disable_player_character3D  // disables player character

// #define zox_disable_render_terrain_chunks
// #define zox_disable_render_ui_3D
// #define zox_disable_render_characters
// #define zox_disable_render_ui

// === Disables ===

// #define zox_disable_logs
// #define zox_disable_terrain
// #define zox_disable_characters3D_voxes

// voxels
// #define zox_disable_terrain_octrees  // disables octrees, uses arrays
// #define zox_disable_closing_octree_nodes
// #define zoxel_disable_close_nodes
// #define zox_disable_hidden_terrain_edge        // hides faces on edge of map
// #define zoxel_voxel_disable_distance_division
// #define voxels_use_octree_pooling

// #define zox_disable_terrain_grid
// #define zoxel_disable_velocity       // disables all movement, used to debug spawning
// #define zoxel_disable_non_vertical_bounce
// #define zox_disable_fog
