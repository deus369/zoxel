// -- Tests / Options --
// #define zoxel_test_chickens
// #define zoxel_test_character3Ds
// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_back
// #define disable_voxel_front
// #define disable_voxel_down
// #define zoxel_test_lines3D
// #define zoxel_test_networking
// #define zoxel_test_brain
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes             // Failing atm, gl error at opengl_draw_triangles
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_character3Ds      // todo
// #define zoxel_test_voxels
// #define zoxel_test_uis
// voxels
#define voxel_octrees
#define voxels_close_octree_nodes
#define voxels_hide_terrain_edge
// #define voxels_terrain_multi_material
// #define zoxel_disable_close_nodes
// #define voxels_disable_streaming
// #define voxels_flat_land
// #define zoxel_voxel_disable_distance_division
// #define voxels_use_octree_pooling
// -- debugs --
#define zox_logs // add logs with printf
// #define log_to_file
#define zoxel_debug_sdl
#define zoxel_debug_opengl
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
//  > target fps is 30 then 33.33 is the ms required, 16.66 if 60 fps
// #define zoxel_log_frame_ms
// #define zoxel_log_frames_per_second
// #define zoxel_time_main_loop
// #define zoxel_time_main_loop_cutoff 0
// #define zoxel_time_main_loop_cutoff 30
// #define zoxel_time_always
// voxels timing
// #define zoxel_time_stream_point_system
// #define zoxel_time_terrain_chunk_system
// #define zoxel_time_chunk_uvs_builds_system
// voxel octrees timing
#define zoxel_time_octree_terrain_chunk_system
#define zoxel_time_octree_chunk_uvs_builds_system
// #define zoxel_time_mesh_uvs_update_system
// idea: generate terrain too at lesser resolutions
// #define zoxel_time_render_3d_uvs
// audio
// #define zoxel_debug_sounds
// #define zoxel_debug_music
// #define zoxel_log_sound_generation
// #define zoxel_log_music_playing
// #define zoxel_slow_music
// #define zoxel_disable_music
// audio timing
// #define zoxel_time_sound_generate_system
// zoxel game
// #define voxels_spawn_terrain