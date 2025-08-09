#if !defined(zoxm_cameras2) && defined(zoxm_transforms2)
#define zoxm_cameras2

zox_tag(CameraFollower2);
#include "prefabs/camera2.c"
#include "systems/_.c"

void spawn_prefabs_cameras2(ecs* world) {
    spawn_prefab_camera2D_follower(world, prefab_camera);
}

zox_begin_module(Cameras2)
    zox_define_tag(CameraFollower2);
    define_systems_cameras2(world);
    add_hook_spawn_prefabs(spawn_prefabs_cameras2);
zox_end_module(Cameras2)

#endif