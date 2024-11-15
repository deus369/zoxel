


#ifdef zox_test_skeletons
    #define zox_is_flatlands
    #define zox_disable_npcs
    // #define zox_transparent_voxes
    // #define zox_disable_skybox
    // #define zox_disable_player_ui
    // #define zox_disable_player_character
    #define zox_spawn_single_npc
    #define zox_enable_bones
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
    #define zox_disable_raycasts3D
    #define zox_disable_raycast_gizmos
    // chunks
    #define zox_disable_block_voxes
    #define zox_disable_streaming
    #define zox_disable_chunk_building
    // physics
    #define zox_disable_collisions
#endif
