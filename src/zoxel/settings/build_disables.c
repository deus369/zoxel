// disables

// #define zoxel_catch_opengl_errors

// #define zox_disable_io

// for web build disable these for now
#ifdef __EMSCRIPTEN__
    #define zox_disable_module_networking
    // #define zox_disable_terrain_textures // this kinda breaks
    #define zox_disable_render_element3D
#endif

// #define zox_disable_music
// #define zox_disable_play_sounds

#define zox_disable_gamepad_stick_as_any_input // used for samsung phone, it's buggy af
#define zox_disable_gamepad_deadzones
// #define zoxel_disable_gamepads

// #define zox_disable_mouse_constraint

// #define zox_disable_set_vox
// #define zox_disable_characters3D        // disables npcs
// #define zox_extra_destroy_terrain_children
// this seems to create more triangles and not dispose them properly
// #define zox_disable_terrain_streaming
// #define zox_disable_chunk_linking
// #define zox_disable_player_character3D  // disables player character
// #define zox_disable_statbars

// #define zox_disable_render_terrain_chunks
// #define zox_disable_render_ui_3D
// #define zox_disable_render_characters
// #define zox_disable_render_ui

// === Disables ===

// #define zox_disable_logs
// #define zox_disable_skybox
// #define zox_disable_terrain
// #define zox_disable_characters3D_voxes

// -- disables --
// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_back
// #define disable_voxel_front
// #define disable_voxel_down

// voxels
// #define zox_disable_terrain_octrees  // disables octrees, uses arrays
// #define zox_disable_closing_octree_nodes
// #define zoxel_disable_close_nodes
// #define zox_disable_hidden_terrain_edge        // hides faces on edge of map
// #define zox_disable_voxels_dynamic_array      // used in mesh generation
// #define zoxel_voxel_disable_distance_division
// #define voxels_use_octree_pooling

// #define zox_disable_terrain_grid
// #define zoxel_disable_velocity       // disables all movement, used to debug spawning
// #define zoxel_disable_non_vertical_bounce
// #define zox_disable_fog      // todo: make work
// #define zox_disable_vox_octrees
