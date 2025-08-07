#if !defined(zoxm_cameras3) && defined(zoxm_transforms3)
#define zoxm_cameras3

#include "prefabs/camera3.c"
#include "systems/_.c"

zox_begin_module(Cameras3)
    prefab_camera_game = spawn_prefab_camera3D(world, prefab_camera);
    define_systems_cameras3(world);
zox_end_module(Cameras3)

#endif