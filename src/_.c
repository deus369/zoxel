#ifndef zox_game
    #define zox_game zoxel
#endif
#define str_macro(x) #x
#define inc_nexus_game(x) str_macro(nexus/x/_.c)
#define zox_nexus_game inc_nexus_game(zox_game)

#define zox_glitch_fix_hierarchy_labels
#define zox_set_camera_firstperson
#define zoxel_time_main_loop_cutoff 33.33f
#define zox_disable_mouse_constraint
#define zox_disable_gamepad_stick_as_any_input // used for samsung phone, it's buggy af
#define zox_disable_gamepad_deadzones
// #define zox_disable_post_processing

#ifdef zox_test_streaming_01
    // #define zox_is_flatlands
    #define zox_disable_npcs
    #define zox_disable_block_voxes
#endif

#ifdef zox_test_skeletons
    #define zox_transparent_skeletons
    #define zox_debug_bones
    #define zox_is_flatlands
    // #define zox_disable_npcs
    // #define zox_disable_skybox
    // #define zox_disable_player_ui
    // #define zox_disable_player_character
    // #define zox_spawn_single_npc
#endif

#ifdef zox_test_settings_00
    // #define zox_disable_skybox
    #define zox_disable_block_voxes  // currently these lag
    // #define zox_disable_npcs
    // #define zox_is_flatlands
#endif

#ifdef zox_test_settings_03
    #define zox_is_flatlands
    #define zox_disable_npcs
    #define zox_disable_block_voxes
    #define zox_disable_frustum_culling
    #define zox_disable_player_ui
    #define zox_disable_player_character
#endif

#ifdef zox_test_settings_02
    #define zox_disable_npcs
    #define zox_disable_player_ui
    #define zox_disable_player_character
#endif

#ifdef zox_test_settings_01
    // terrain
    #define zox_is_flatlands
    #define zox_disable_npcs
    #define zox_disable_terrain_generation
    #define zox_disable_chunks_rendering
    // player
    #define zox_disable_player_ui
    #define zox_disable_player_character
    // chunks
    #define zox_disable_block_voxes
    #define zox_disable_streaming
    #define zox_disable_chunk_building
    // physics
    #define zox_disable_collisions
#endif
