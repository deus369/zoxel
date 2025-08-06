#ifndef zoxm_space
#define zoxm_space

// one day we will actually make this abuot space

// hmm
char* player_vox_model = "tall_cube";
#include "spawns/player.c"
#include "util/_.c"
#include "game/_.c"
#include "debug/_.c"
// raycasting
#include "systems/chunk3_raycast.c"
#include "systems/raycast_gizmo.c"

zox_begin_module(Space)
    zox_system(Chunk3RaycastSystem, EcsOnUpdate,
            [in] cameras.CameraLink,
            [in] chunks3.VoxLink,
            [in] chunks3.RaycastRange,
            [out] chunks3.RaycastVoxelData);
    zox_system_1(RaycastGizmoSystem, EcsPreStore,
            [in] chunks3.RaycastVoxelData);
    add_to_event_game_state((zox_game_event) { &players_game_state });
    add_hook_on_boot(on_boot_space);
zox_end_module(Space)

#endif