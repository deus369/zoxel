#ifndef zoxel_cameras
#define zoxel_cameras

// zoxel_settings
#define max_cameras 16
const float camera_far_distance = 6000;
int main_cameras_count = 1;
const int camera_fov = 90;
const float camera_limit_x = 1.25f;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[1];
// zoxel_component_declares
zox_declare_tag(Camera)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraFollower2D)
zox_declare_tag(UICamera)
zox_component(ProjectionMatrix, float4x4)
zox_component(ViewMatrix, float4x4)
zox_component(ScreenDimensions, int2)
zox_component(ScreenPosition, int2)
zox_component(FieldOfView, float)
zox_component(CameraNearDistance, float)
zox_component(CameraLink, ecs_entity_t)
zox_component(CameraTarget, ecs_entity_t)
zox_byte_component(FreeRoam)
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

void spawn_prefabs_cameras(ecs_world_t *world) {
    spawn_camera_base_prefab(world);
    spawn_prefab_free_camera(world);
    spawn_camera2D_follower_prefab(world);
}

zox_begin_module(Cameras)
// zoxel_component_defines
zox_define_tag(Camera)
zox_define_tag(FirstPersonCamera)
zox_define_tag(CameraFollower2D) // Until fix is found. \todo Fix this, readd it back here where it belongs.
zox_define_tag(UICamera)
zox_define_component(CameraLink)
zox_define_component(CameraTarget)
zox_define_component(ProjectionMatrix)
zox_define_component(ViewMatrix)
zox_define_component(ScreenDimensions)
zox_define_component(ScreenPosition)
zox_define_component(FieldOfView)
zox_define_component(CameraNearDistance)
zox_define_component(FreeRoam)
// zoxel_system_defines
#ifdef main_thread_projection_matrix_system
    zox_system_1(ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
#else
    zox_system(ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
#endif
zox_system(ViewMatrixSystem, EcsPreStore, [in] Position3D, [in] Rotation3D, [in] ProjectionMatrix, [out] ViewMatrix)
zox_system(CameraFollow2DSystem, EcsOnUpdate, [none] CameraFollower2D, [in] FreeRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D)
zoxel_end_module(Cameras)

//   todo: Custom name for namespaces used in flecs
//       const char* nm_zoxel_cameras = "Zoxel.cameras";
//       zox_module(world, cameras, nm_zoxel_cameras);

#endif