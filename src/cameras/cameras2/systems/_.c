#include "camera2_follow_system.c"

void define_systems_cameras2(ecs_world_t *world) {
    zox_system(Camera2FollowSystem, EcsPostUpdate,
        [in] cameras.CanRoam,
        [in] cameras.CameraTarget,
        [out] transforms3.Position3D,
        [out] transforms3.Rotation3D,
        [none] cameras2.CameraFollower2)
}