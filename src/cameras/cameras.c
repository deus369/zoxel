#if !defined(zox_mod_cameras) && defined(zox_mod_transforms)
#define zox_mod_cameras

// todo: use this for ViewMatrix (current use) and use ViewMatrix just as Inverted TransformMatrix
// todo: refactor cameras do they even need ScreenPosition? we should just have CanvasLinks, and each camera is linked to a bunch? idk

#include "data/camera_spawn_data.c"
#include "data/bounds.c"
#include "data/plane.c"
#include "data/settings.c"
zox_declare_tag(Camera)
zox_declare_tag(Camera2D)
zox_declare_tag(Camera3D)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraFollower2D)
zox_declare_tag(CameraUI)
zox_declare_tag(RenderCamera)
zox_declare_tag(RenderTexture)
zox_declare_tag(ElementBillboard)
zox_component_byte(CanRoam)
zox_component_byte(CameraMode)
zox_component_byte(CameraViewing)
zox_component_float(FieldOfView)
zox_component_float(CameraNearDistance)
zox_component_entity(CameraLink)
zox_component_entity(CameraTarget)
zox_component_entity(CameraFollowLink)
zox_component_int2(ScreenPosition)
zox_component_float4(ScreenToCanvas)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4) // todo: rename to ViewProjectionMatrix instead
// zox_component(ViewProjectionMatrix, float4x4)
zox_memory_component(FrustumCorners, double3)
zox_memory_component(CameraPlanes, plane)
zox_component_entity(RenderTextureLink)
#include "util/camera_mode.c"
#include "util/position.c"
#include "util/bounds_util.c"
#include "util/camera_util.c"
#include "util/frustum_util.c"
#include "util/planes_util.c"
#include "util/debug_util.c"
#include "tests/planes_tests.c"
#include "prefabs/prefabs.c"
#include "systems/systems.c"

zox_begin_module(Cameras)
    zox_define_tag(Camera)
    zox_define_tag(Camera2D)
    zox_define_tag(Camera3D)
    zox_define_tag(FirstPersonCamera)
    zox_define_tag(CameraFollower2D)
    zox_define_tag(CameraUI)
    zox_define_tag(RenderCamera)
    zox_define_tag(RenderTexture)
    zox_define_tag(ElementBillboard)
    zox_define_component_entity(RenderTextureLink)
    zox_define_component_byte(CanRoam)
    zox_define_component_byte(CameraMode)
    zox_define_component_byte(CameraViewing)
    zox_define_component_float(FieldOfView)
    zox_define_component_float(CameraNearDistance)
    zox_define_component_int2(ScreenPosition)
    zox_define_component_entity(CameraLink)
    zox_define_component_entity(CameraTarget)
    zox_define_component_entity(CameraFollowLink)
    zox_define_component(ProjectionMatrix)
    zox_define_component(ViewMatrix)
    // zox_define_component(ViewProjectionMatrix)
    zox_define_component_float4(ScreenToCanvas)
    zox_define_memory_component(FrustumCorners)
    zox_define_memory_component(CameraPlanes)
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
    spawn_prefabs_cameras(world);
zoxel_end_module(Cameras)

#endif
