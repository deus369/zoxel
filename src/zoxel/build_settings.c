// -- debugs --
#define zox_logs                    // enables logging
// #define log_to_file              // logs go to a file
// #define zoxel_debug_sdl          // debugs sdl app
// #define zoxel_debug_opengl       // debugs opengl
// #define zoxel_debug_audio        // debugs sdl audio
// #define zoxel_debug_input        // debugs sdl input
// #define zoxel_entity_names       // sets entity names
// #define zoxel_catch_opengl_errors
// #define zoxel_debug_vox_read
//! \todo Fix pathing for android, cannot get resources there.
// #define zoxel_debug_pathing 
// #define zoxel_debug_prefabs
// #define zoxel_debug_spawns
// #define debug_element_position_change_query
// #define debug_viewport_resize
// #define zoxel_debug_element_raycasting
// #define debug_ui_positioning
// #define debug_ui_scaling
// #define zoxel_time_render_loop
// Timings
// #define zoxel_log_frame_ms
// #define zoxel_log_frames_per_second
// #define zoxel_time_main_loop                    // enables time debugging of main loop
//  > target fps is 30 then 33.33 is the ms required, 16.66 if 60 fps
#define zoxel_time_main_loop_cutoff 16.66       // 1000 / 60 = 16.66 | 1000 / 30 = 33.33
// #define zoxel_time_main_loop_cutoff 0
// #define zoxel_time_always
// voxels timing
// #define zoxel_time_stream_point_system
// #define zoxel_time_terrain_chunk_system
// #define zoxel_time_chunk_uvs_builds_system
// voxel octrees timing
// #define zoxel_time_octree_terrain_chunk_system
// #define zoxel_time_octree_chunk_builds_system
// #define zoxel_time_mesh_uvs_update_system
// idea: generate terrain too at lesser resolutions
// #define zoxel_time_render_3d_uvs
// audio
// #define zoxel_debug_sounds
// #define zoxel_debug_music
// #define zoxel_log_sound_generation
// #define zoxel_log_music_playing
// #define zoxel_slow_music
// audio timing
// #define zoxel_time_sound_generate_system
// #define zoxel_debug_zext_updates
// #define zoxel_debug_zigel_updates
// #define debug_ui_positioning
// -- testing --
// #define zoxel_test_chickens
// #define zoxel_test_character3Ds
// #define zoxel_test_lines3D
// #define zoxel_test_networking
// #define zoxel_test_brain
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes             // Failing atm, gl error at opengl_draw_triangles
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_character3Ds      // todo
// #define zoxel_test_voxels
// #define zoxel_test_uis
// -- disables --
// #define zoxel_disable_music
// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_back
// #define disable_voxel_front
// #define disable_voxel_down
// -- settings --
// voxels
#define voxel_octrees                   // use octrees instead of arrays
#define voxels_close_octree_nodes       // closes nodes in terrain gen
#define voxels_hide_terrain_edge        // hides faces on edge of map
#define zoxel_voxels_dynamic_array      // used in mesh generation
// #define voxels_terrain_multi_material
// #define zoxel_disable_close_nodes
// #define voxels_disable_streaming
// #define voxels_flat_land
// #define zoxel_voxel_disable_distance_division
// #define voxels_use_octree_pooling
// -- zoxel game --
#define voxels_spawn_terrain