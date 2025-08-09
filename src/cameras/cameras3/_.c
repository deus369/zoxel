#if !defined(zoxm_cameras3) && defined(zoxm_transforms3)
#define zoxm_cameras3

#include "prefabs/camera3.c"
#include "systems/_.c"

void spawn_prefabs_cameras3(ecs* world) {
    prefab_camera_game = spawn_prefab_camera3D(world, prefab_camera);
}

zox_begin_module(Cameras3)
    define_systems_cameras3(world);
    add_hook_spawn_prefabs(spawn_prefabs_cameras3);
zox_end_module(Cameras3)

#endif