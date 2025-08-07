#include "camera3_follow_system.c"

void define_systems_cameras3(ecs *world) {
    zox_system(Camera3FollowSystem, EcsOnUpdate,
        [in] cameras.CameraFollowLink,
        [in] transforms3.LocalPosition3D,
        [out] transforms3.Position3D)
}