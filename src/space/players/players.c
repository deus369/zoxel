#ifndef zoxel_players
#define zoxel_players

zoxel_declare_tag(Player2D)
zoxel_declare_tag(Player3D)
zoxel_declare_tag(PlayerCharacter)
zoxel_declare_tag(PlayerCharacter2D)
zoxel_declare_tag(PlayerCharacter3D)
ecs_entity_t local_player;
#include "prefabs/player_character2D.c"
#include "prefabs/player_character3D.c"
#include "util/player_character2D.c"
#include "util/player_character3D.c"
#include "systems/player2D_move_system.c"
#include "systems/player2D_test_system.c"
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/free_camera_move_system.c"
#include "systems/free_camera_rotate_system.c"
#include "systems/free_camera_toggle_system.c"
#include "systems/free_camera_disable_movement_system.c"

zoxel_begin_module(Players)
zoxel_define_tag(Player2D)
zoxel_define_tag(Player3D)
zoxel_define_tag(PlayerCharacter)
zoxel_define_tag(PlayerCharacter2D)
zoxel_define_tag(PlayerCharacter3D)
spawn_player_character2D_prefab(world);
spawn_player_character3D_prefab(world);
#ifdef zoxel_physics2D
zoxel_filter(playerCharacter2DQuery2, world, [none] PlayerCharacter2D, [out] Acceleration2D, [in] Velocity2D, [in] physics.DisableMovement)
zoxel_system_ctx(world, Player2DMoveSystem, EcsOnUpdate, playerCharacter2DQuery2, [in] Keyboard)
#endif
#ifdef zoxel_physics3D
zoxel_filter(playerCharacter3DQuery, world, [none] PlayerCharacter3D, [out] Acceleration3D, [in] Velocity3D, [in] physics.DisableMovement, [in] Rotation3D)
zoxel_system_ctx(world, Player3DMoveSystem, EcsOnUpdate, playerCharacter3DQuery, [in] Keyboard)
zoxel_filter(playerCharacter3DQuery2, world, [none] PlayerCharacter3D, [out] Alpha3D, [in] physics.DisableMovement)
zoxel_system_ctx(world, Player3DRotateSystem, EcsOnUpdate, playerCharacter3DQuery2, [in] Mouse)
#endif
zoxel_filter(cameraQuery, world, [none] cameras.Camera, [in] cameras.FreeRoam, [out] Position3D, [out] Rotation3D)
zoxel_filter(cameraQuery2, world, [none] cameras.Camera, [in] cameras.FreeRoam,
#ifndef zoxel_quaternion_camera
    [out] Euler)
#else
    [out] Rotation3D)
#endif
zoxel_filter(cameraQuery3, world, [none] cameras.Camera, [out] cameras.FreeRoam)
zoxel_filter(playerCharacter2DQuery3, world, [none] PlayerCharacter, [out] physics.DisableMovement)
zoxel_system_ctx(world, FreeCameraMoveSystem, EcsOnUpdate, cameraQuery, [in] Keyboard)
zoxel_system_ctx(world, FreeCameraRotateSystem, EcsOnUpdate, cameraQuery2, [in] Mouse)
zoxel_system_ctx(world, FreeCameraToggleSystem, EcsOnUpdate, cameraQuery3, [in] Mouse)
zoxel_system_ctx(world, FreeCameraDisableMovementSystem, EcsOnUpdate, playerCharacter2DQuery3, [in] Mouse)
zoxel_system(Player2DTestSystem, EcsOnUpdate, [in] Keyboard)
zoxel_system(Player2DTestMainThreadSystem, EcsOnStore, [in] Keyboard)
zoxel_end_module(Players)

//#if zoxel_particles2D
//! Needed for bulk spawning. Still crashes.
// \todo Spawning Queries in Initialize function as they depend on other Modules
// zoxel_system_1(Player2DTestSystem, EcsOnUpdate, [in] Keyboard)
// ecs_system(world, { .entity = ecs_id(Player2DTestSystem), .no_readonly = 1 });
// this has to update after reset systems (as gen is stuck on main thread, running before everything)

#endif