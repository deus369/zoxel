#if !defined(zox_mod_cameras) && defined(zox_mod_transforms)
#define zox_mod_cameras

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
zox_component_byte(CanRoam)
zox_component_byte(CameraMode)
zox_component_byte(CameraViewing)
zox_component_float(FieldOfView)
zox_component_float(CameraNearDistance)
zox_component_entity(CameraLink)
zox_component_entity(CameraTarget)
zox_component_entity(CameraFollowLink)
zox_component_int2(ScreenDimensions)
zox_component_int2(ScreenPosition)
zox_component_float4(ScreenToCanvas)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4) // todo: use ViewProjectionMatrix instead
zox_component(ViewProjectionMatrix, float4x4)
zox_memory_component(CameraPlanes, plane)
#include "fun/camera_util.c"
#include "util/bounds_util.c"
#include "util/camera_util.c"
#include "util/frustum_util.c"
#include "util/planes_util.c"
#include "util/debug_util.c"
#include "tests/planes_tests.c"
#include "prefabs/base_camera.c"
#include "prefabs/camera2D.c"
#include "prefabs/ui_camera.c"
#include "prefabs/free_camera.c"
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"
#include "systems/camera2D_follow_system.c"
#include "systems/camera3D_follow_system.c"
#include "systems/camera_frustum_system.c"
#include "systems/camera_debug_system.c"
#include "systems/camera_draw_frustum_system.c"

void spawn_prefabs_cameras(ecs_world_t *world) {
    spawn_camera_base_prefab(world);
    spawn_prefab_free_camera(world);
    spawn_prefab_camera2D_follower(world);
}

zox_begin_module(Cameras)
zox_define_tag(Camera)
zox_define_tag(Camera2D)
zox_define_tag(Camera3D)
zox_define_tag(FirstPersonCamera)
zox_define_tag(CameraFollower2D)
zox_define_tag(CameraUI)
zox_define_component_byte(CanRoam)
zox_define_component_byte(CameraMode)
zox_define_component_byte(CameraViewing)
zox_define_component_float(FieldOfView)
zox_define_component_float(CameraNearDistance)
zox_define_component_int2(ScreenDimensions)
zox_define_component_int2(ScreenPosition)
zox_define_component_entity(CameraLink)
zox_define_component_entity(CameraTarget)
zox_define_component_entity(CameraFollowLink)
zox_define_component(ProjectionMatrix)
zox_define_component(ViewMatrix)
zox_define_component(ViewProjectionMatrix)
zox_define_component_float4(ScreenToCanvas)
zox_define_memory_component(CameraPlanes)
zox_system(Camera2DFollowSystem, EcsPostUpdate, [in] CanRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D, [none] CameraFollower2D)
zox_system(Camera3DFollowSystem, EcsPostUpdate, [in] CameraFollowLink, [in] LocalPosition3D, [out] Position3D)
zox_system(ViewMatrixSystem, zox_camera_stage, [in] TransformMatrix, [in] ProjectionMatrix, [out] ViewMatrix)
zox_system(ProjectionMatrixSystem, zox_camera_stage, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
// single thread while debugging
zox_system_1(CameraFrustumSystem, zox_camera_stage, [in] ViewMatrix, [in] TransformMatrix, [in] ProjectionMatrix, [out] CameraPlanes, [out] Position3DBounds, [none] Camera, [none] Camera3D)
#ifdef zox_draw_frustum
zox_system_1(CameraDrawFrustumSystem, main_thread_pipeline, [in] TransformMatrix, [in] ProjectionMatrix, [in] ViewMatrix, [none] Camera3D)
#endif
#ifdef zox_debug_camera_frustum
zox_system_1(CameraDebugSystem, main_thread_pipeline, [in] CameraPlanes, [none] Camera)
#endif
spawn_prefabs_cameras(world);
zoxel_end_module(Cameras)

// todo: use this for ViewMatrix (current use) and use ViewMatrix just as Inverted TransformMatrix
// todo: refactor cameras do they even need ScreenPosition? we should just have CanvasLinks, and each camera is linked to a bunch? idk

#endif
