#ifndef zoxel_cameras
#define zoxel_cameras

// zoxel_settings
// EcsPreStore | EcsPostUpdate
#define zox_camera_stage EcsPreStore
#include "settings/settings.c"
// shared data
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[max_cameras];
// zoxel_component_declares
zox_declare_tag(Camera)
zox_declare_tag(Camera2D)
zox_declare_tag(Camera3D)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraFollower2D)
zox_declare_tag(UICamera)
zox_component_byte(FreeRoam)
zox_component_byte(CanFreeRoam)
zox_component_byte(CameraMode)
zox_component_float(FieldOfView)
zox_component_float(CameraNearDistance)
zox_component_int2(ScreenDimensions)
zox_component_int2(ScreenPosition)
zox_entity_component(CameraLink)
zox_entity_component(CameraTarget)
zox_entity_component(CameraFollowLink)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4)
zox_component_float4(ScreenToCanvas)
// zoxel_prefab_includes
#include "prefabs/base_camera.c"
#include "prefabs/camera2D.c"
#include "prefabs/ui_camera.c"
#include "prefabs/free_camera.c"
// zoxel_function_includes
#include "fun/camera_util.c"
// zoxel_system_declares
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"
#include "systems/camera2D_follow_system.c"
#include "systems/camera3D_follow_system.c"

void spawn_prefabs_cameras(ecs_world_t *world) {
    spawn_camera_base_prefab(world);
    spawn_prefab_free_camera(world);
    spawn_prefab_camera2D_follower(world);
}

zox_begin_module(Cameras)
// zoxel_component_defines
zox_define_tag(Camera)
zox_define_tag(Camera2D)
zox_define_tag(Camera3D)
zox_define_tag(FirstPersonCamera)
zox_define_tag(CameraFollower2D)
zox_define_tag(UICamera)
zox_define_component_byte(FreeRoam)
zox_define_component_byte(CanFreeRoam)
zox_define_component_byte(CameraMode)
zox_define_component_float(FieldOfView)
zox_define_component_float(CameraNearDistance)
zox_define_component_int2(ScreenDimensions)
zox_define_component_int2(ScreenPosition)
zox_define_component(CameraLink)
zox_define_component(CameraTarget)
zox_define_component(CameraFollowLink)
zox_define_component(ProjectionMatrix)
zox_define_component(ViewMatrix)
zox_define_component_float4(ScreenToCanvas)
// zoxel_system_defines
zox_system(Camera2DFollowSystem, EcsPostUpdate, [none] CameraFollower2D, [in] FreeRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D)
zox_system(Camera3DFollowSystem, EcsPostUpdate, [in] CameraFollowLink, [in] LocalPosition3D, [out] Position3D)
zox_system(ViewMatrixSystem, zox_camera_stage, [in] Position3D, [in] Rotation3D, [in] ProjectionMatrix, [out] ViewMatrix)
zox_system(ProjectionMatrixSystem, zox_camera_stage, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
zoxel_end_module(Cameras)

#endif
