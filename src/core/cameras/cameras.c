#ifndef zox_cameras
#define zox_cameras

#include "settings/settings.c"
#include "data/plane.c"
zox_declare_tag(Camera)
zox_declare_tag(Camera2D)
zox_declare_tag(Camera3D)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraFollower2D)
zox_declare_tag(CameraUI)
zox_component_byte(FreeRoam)
zox_component_byte(CanFreeRoam)
zox_component_byte(CameraMode)
zox_component_byte(CameraViewing)
zox_component_float(FieldOfView)
zox_component_float(CameraNearDistance)
zox_component_int2(ScreenDimensions)
zox_component_int2(ScreenPosition)
zox_component_entity(CameraLink)
zox_component_entity(CameraTarget)
zox_component_entity(CameraFollowLink)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4)
zox_component_float4(ScreenToCanvas)
zox_memory_component(CameraPlanes, plane)
#include "fun/camera_util.c"
#include "util/camera_util.c"
#include "util/planes_util.c"
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

int get_label_camera(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return buffer_index;
    const float3 position3D = zox_get_value(camera, Position3D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "camera [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    return buffer_index;
}

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
zox_define_component_byte(FreeRoam)
zox_define_component_byte(CanFreeRoam)
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
zox_define_component_float4(ScreenToCanvas)
zox_define_memory_component(CameraPlanes)
zox_system(Camera2DFollowSystem, EcsPostUpdate, [in] FreeRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D, [none] CameraFollower2D)
zox_system(Camera3DFollowSystem, EcsPostUpdate, [in] CameraFollowLink, [in] LocalPosition3D, [out] Position3D)
zox_system(ViewMatrixSystem, zox_camera_stage, [in] TransformMatrix, [in] ProjectionMatrix, [out] ViewMatrix)
zox_system(ProjectionMatrixSystem, zox_camera_stage, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
zox_system(CameraFrustumSystem, zox_camera_stage, [in] ViewMatrix, [out] CameraPlanes, [none] Camera)
#ifdef zox_debug_camera_frustum
zox_system_1(CameraDebugSystem, main_thread_pipeline, [in] CameraPlanes, [in] TransformMatrix, [none] Camera)
#endif
zoxel_end_module(Cameras)

#endif
