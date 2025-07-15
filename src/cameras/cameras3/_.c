#if !defined(zox_mod_cameras3) && defined(zox_mod_transforms3)
#define zox_mod_cameras3

#include "prefabs/camera3.c"
#include "systems/_.c"

zox_begin_module(Cameras3)
    prefab_camera_game = spawn_prefab_camera3D(world, prefab_camera);
    define_systems_cameras3(world);
zox_end_module(Cameras3)

#endif