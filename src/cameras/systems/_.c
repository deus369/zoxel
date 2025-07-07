#include "projection_matrix_system.c"
#include "view_matrix_system.c"
#include "camera2D_follow_system.c"
#include "camera3D_follow_system.c"
#include "camera_frustum_system.c"
#include "billboard_system.c"
// #include "camera_debug_system.c"
//#include "camera_draw_frustum_system.c"
//#include "camera_planes_draw_system.c"

void define_systems_cameras(ecs_world_t *world) {
    zox_system(Camera2DFollowSystem, EcsPostUpdate, [in] cameras.CameraMode, [in] CameraTarget, [out] transforms3.d.Position3D, [out] transforms3.d.Rotation3D, [none] CameraFollower2D)
    zox_system(Camera3DFollowSystem, EcsOnUpdate, [in] CameraFollowLink, [in] transforms3.d.LocalPosition3D, [out] transforms3.d.Position3D)
    zox_system(ViewMatrixSystem, zox_camera_stage, [in] transforms3.d.TransformMatrix, [in] ProjectionMatrix, [out] ViewMatrix)
    zox_system(ProjectionMatrixSystem, zox_camera_stage, [in] generic.ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
    zox_system(CameraFrustumSystem, zox_camera_stage, [in] ViewMatrix, [out] FrustumCorners, [out] generic.Position3DBounds, [out] CameraPlanes, [none] Camera, [none] Camera3D)
    zox_system(BillboardSystem, zox_transforms_stage, [in] transforms3.d.Position3D, [out] transforms3.d.Rotation3D, [none] ElementBillboard)
    #ifdef zox_draw_frustum
    //zox_system_1(CameraPlanesDrawSystem, zox_pip_mainthread, [in] CameraPlanes, [none] Camera3D)
    //zox_system_1(FrustumDrawSystem, zox_pip_mainthread, [in] FrustumCorners, [none] Camera3D)
    #endif
    #ifdef zox_debug_camera_frustum
    // zox_system_1(CameraDebugSystem, zox_pip_mainthread, [in] CameraPlanes, [none] Camera)
    #endif
}