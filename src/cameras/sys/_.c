#include "projection_matrix_system.c"
#include "view_matrix_system.c"
#include "billboard_system.c"
#include "viewport_resize_system.c"

#ifdef frustumdouble
    #include "frustum_d3.c"
#else
    #include "frustum_f3.c"
#endif

// #include "camera_debug_system.c"
// #include "camera_draw_frustum_system.c"
// #include "camera_planes_draw_system.c"

void define_systems_cameras(ecs *world) {
    zox_system(ViewMatrixSystem, zoxp_cameras,
        [in] transforms3.TransformMatrix,
        [in] ProjectionMatrix,
        [out] ViewMatrix)
    zox_system(ProjectionMatrixSystem, zoxp_cameras,
        [in] generic.ScreenDimensions,
        [in] FieldOfView,
        [in] CameraNearDistance,
        [out] ProjectionMatrix)
    zox_system(CameraFrustumSystem, zoxp_cameras,
        [in] ViewMatrix,
        [out] FrustumCorners,
        [out] generic.Position3DBounds,
        [out] CameraPlanes,
        [none] Camera,
        [none] Camera3D)
    zox_system(BillboardSystem, zox_transforms_stage,
        [in] transforms3.Position3D,
        [out] transforms3.Rotation3D,
        [none] ElementBillboard)
    if (!headless) {
        zox_system(ViewportResizeSystem, EcsOnUpdate,
            [in] apps.WindowSizeDirty,
            [in] apps.WindowSize,
            [in] CameraLinks,
            [none] apps.App);
    }
    #ifdef zox_draw_frustum
    //zox_system_1(CameraPlanesDrawSystem, zoxp_mainthread, [in] CameraPlanes, [none] Camera3D)
    //zox_system_1(FrustumDrawSystem, zoxp_mainthread, [in] FrustumCorners, [none] Camera3D)
    #endif
    #ifdef zox_debug_camera_frustum
    // zox_system_1(CameraDebugSystem, zoxp_mainthread, [in] CameraPlanes, [none] Camera)
    #endif
}