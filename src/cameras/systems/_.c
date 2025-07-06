#include "projection_matrix_system.c"
#include "view_matrix_system.c"
#include "camera2D_follow_system.c"
#include "camera3D_follow_system.c"
#include "camera_frustum_system.c"
#include "camera_debug_system.c"
#include "camera_draw_frustum_system.c"
#include "camera_planes_draw_system.c"
#include "billboard_system.c"

void define_systems_cameras(ecs_world_t *world) {
    zox_system(Camera2DFollowSystem, EcsPostUpdate, [in] CanRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D, [none] CameraFollower2D)
    zox_system(Camera3DFollowSystem, EcsOnUpdate, [in] CameraFollowLink, [in] LocalPosition3D, [out] Position3D)
    zox_system(ViewMatrixSystem, zox_camera_stage, [in] TransformMatrix, [in] ProjectionMatrix, [out] ViewMatrix)
    zox_system(ProjectionMatrixSystem, zox_camera_stage, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
    zox_system(CameraFrustumSystem, zox_camera_stage, [in] ViewMatrix, [out] FrustumCorners, [out] Position3DBounds, [out] CameraPlanes, [none] Camera, [none] Camera3D)
    zox_system(BillboardSystem, zox_transforms_stage, [in] Position3D, [out] Rotation3D, [none] ElementBillboard)
    #ifdef zox_draw_frustum
    zox_system_1(CameraPlanesDrawSystem, zox_pip_mainthread, [in] CameraPlanes, [none] Camera3D)
    zox_system_1(FrustumDrawSystem, zox_pip_mainthread, [in] FrustumCorners, [none] Camera3D)
    #endif
    #ifdef zox_debug_camera_frustum
    zox_system_1(CameraDebugSystem, zox_pip_mainthread, [in] CameraPlanes, [none] Camera)
    #endif
}