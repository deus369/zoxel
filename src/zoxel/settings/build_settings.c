// Here? select which zoxel modules I shall use?
// #define zoxel_include_vulkan
#define zoxel_include_players

// temp
// #define zox_terrain_preset_tiny
// #define zox_terrain_preset_small
// #define zox_terrain_preset_large
// #define zox_terrain_preset_enormous

// === Disables ===

// #define zox_disable_logs
// #define zox_disable_skybox
// #define zox_disable_terrain
// #define zox_disable_characters3D
// #define zox_disable_characters3D_voxes

// === Debugs ===

// #define zox_time_create_terrain
// #define zox_disable_render_ui
// #define zox_disable_render_terrain_chunks
// #define zox_disable_render_characters
// #define zox_disable_render_ui_3D

// #define zox_check_render_camera_errors

// #define zox_print_sdl                       // debugs sdl app
// #define zoxel_debug_opengl                  // debugs opengl
// #define zoxel_catch_opengl_errors        // opengl test

// -- in game ui debugs --
// #define zoxel_debug_fps
// #define zoxel_debug_quads
// #define zoxel_debug_settings             // debugs zoxel settings
// #define zoxel_debug_audio                // debugs sdl audio
// #define zoxel_debug_input                // debugs sdl input
// #define zoxel_debug_eternal_rotation     // debugs euler in main menu
// #define zoxel_debug_pathing 
// #define zoxel_debug_prefabs
// #define zoxel_debug_spawns
// #define debug_ui_positioning
// #define debug_ui_scaling
// #define zox_debug_ui_trails      // shows a line from the ui holder to the ui

// === Logging Debugs ===

// #define zox_debug_generic_events

// === Settings ===

// #define zoxel_seed_666  // tests seed at 666
// #define log_to_file              // logs go to a file


// === Tests ===

// #define zox_play_game_on_start
// #define zox_terrain_preset_small
// #define zox_terrain_preset_medium
// #define zox_test_game_keys
// #define zox_test_quaternion_camera

// === Checks ===

// #define zox_check_current_time

// === Timing ===

// > target fps is 30 then 33.33 is the ms required, 16.66 if 60 fps
#define zoxel_time_main_loop_cutoff 33.33f       // 1000 / 60 = 16.66 | 1000 / 30 = 33.33
// #define zoxel_time_main_loop_cutoff 16.66f       // 1000 / 60 = 16.66 | 1000 / 30 = 33.33
#define zoxel_time_main_loop                    // enables time debugging of main loop
// #define zoxel_time_main_loop_cutoff 0.001
// #define zoxel_time_always
// #define zoxel_time_zext_update_system
// #define zoxel_time_render_loop

// -- debugs --
// #define zoxel_entity_names       // sets entity names
// #define zoxel_debug_vox_read
//! \todo Fix pathing for android, cannot get resources there.
// #define debug_element_position_change_query
// #define debug_viewport_resize
// #define zox_debug_log_element_raycasting
// Timings
// #define zoxel_log_frame_ms
// #define zoxel_log_frames_per_second
// tests for single thread systems, I get alot more ms timing there
// #define main_thread_zext_update_system
// voxels timing
// #define zoxel_time_stream_point_system           
// #define zoxel_time_terrain_chunk_system
// #define zoxel_time_chunk_uvs_builds_system       // for non octree chunk building

// voxel octrees timing
// #define zoxel_time_octree_terrain_chunk_system      // for octree terrain generation
// #define zoxel_time_octree_chunk_builds_system    // for octree chunk building
// #define zoxel_time_chunk_colors_builds_system
// #define zoxel_time_octree_chunk_builds_system_cutoff 0 //12.0f
// #define zoxel_time_mesh_uvs_update_system        // uploading terrain chunk mesh data
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
// #define zoxel_test_networking
// #define zoxel_test_brain         // testing a brain
// #define zoxel_test_character2Ds
// #define zoxel_test_cubes             // Failing atm, gl error at opengl_draw_triangles
// #define zoxel_test_cubes_textured    // wip
// #define zoxel_test_uis
// -- disables --
// #define zoxel_disable_music
// #define disable_voxel_left
// #define disable_voxel_right
// #define disable_voxel_back
// #define disable_voxel_front
// #define disable_voxel_down
// voxels
// #define zox_disable_terrain_octrees  // disables octrees, uses arrays
// #define zox_disable_closing_octree_nodes
// #define zox_disable_hidden_terrain_edge        // hides faces on edge of map
// #define zox_disable_voxels_dynamic_array      // used in mesh generation
// #define voxels_terrain_multi_material
// #define zoxel_disable_close_nodes
// #define voxels_disable_streaming
// #define zoxel_voxel_disable_distance_division
// #define voxels_use_octree_pooling
// -- zoxel game --
// #define zox_disable_terrain_grid
// #define zoxel_voxes_color_randomize
// #define zoxel_debug_vox_read
// #define zoxel_is_flat_height
// #define zoxel_debug_chunk_link_system
// #define zoxel_debug_chunk_link_system_test
// Fixed color shader gpu things and systems
// #define zoxel_log_characters_count
// #define zoxel_log_files
// #define zoxel_disable_velocity       // disables all movement, used to debug spawning
// #define zoxel_spawn_character3Ds         // spawn x penguins
// player testing
// #define zoxel_debug_basic_collision3D_system
// #define zoxel_tests_rotate_by_keys
// #define zoxel_disable_non_vertical_bounce
// #define zoxel_inputs_debug_gamepad
// #define zoxel_inputs_debug_gamepad_sos
// test settings
// #define zox_disable_fog      // todo: make work
// #define zox_terrain_preset_large
// #define zox_grayboxing
// #define zox_disable_vox_octrees
// #define zox_test_voxel_mesh
// #define zoxel_debug_bounds          // renders a bounding box rotated for characters (by default)
// #define zoxel_debug_transforms      // renders an axis for movement of characters
// --- latest test here below ---
// #define zox_test_voxes
// #define zoxel_test_single_character3Ds      // spawn 1 penguin
// #define zoxel_disable_attach_on_start