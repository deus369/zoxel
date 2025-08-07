#if !defined(zoxm_cameras2) && defined(zoxm_transforms2)
#define zoxm_cameras2

zox_declare_tag(CameraFollower2)
#include "prefabs/camera2.c"
#include "systems/_.c"

zox_begin_module(Cameras2)
    zox_define_tag(CameraFollower2)
    spawn_prefab_camera2D_follower(world, prefab_camera);
    define_systems_cameras2(world);
zox_end_module(Cameras2)

#endif