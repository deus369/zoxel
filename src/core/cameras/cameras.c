#ifndef zoxel_cameras
#define zoxel_cameras

#define max_cameras 16
const float camera_far_distance = 6000;
int main_cameras_count = 1;
const int camera_fov = 90;  // 60
const float camera_limit_x = 1.25f; // 0.8f
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[1];
zox_declare_tag(Camera)
zox_declare_tag(FirstPersonCamera)
zox_declare_tag(CameraFollower2D)  // a tag for a camera that follows a Character2D
zox_declare_tag(UICamera)
zox_component(ProjectionMatrix, float4x4) //! Used for the cameras frustrum.
zox_component(ViewMatrix, float4x4)       //! Used with all the materials to render the scene.
zox_component(ScreenDimensions, int2)     //! Has dimensions of the camera viewport screen. Used to calculate a camera frustrum.
zox_component(ScreenPosition, int2)
zox_component(FieldOfView, float)         //! Used to calculate a camera frustrum.
zox_component(CameraNearDistance, float)
zox_component(CameraLink, ecs_entity_t)   //! A link to a Camera
zox_component(CameraTarget, ecs_entity_t) //! A link to a Camera Target entity.
zoxel_byte_component(FreeRoam)             //! Used to free roam a camera.
#include "prefabs/base_camera.c"
#include "prefabs/camera2D.c"
#include "prefabs/ui_camera.c"
#include "prefabs/free_camera.c"
#include "fun/camera_util.c"
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"
#include "systems/camera2D_follow_system.c"

zox_begin_module(Cameras)
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
#ifdef main_thread_projection_matrix_system
    zox_system_1(ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
#else
    zox_system(ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
#endif
zox_system(ViewMatrixSystem, EcsPreStore, [in] Position3D, [in] Rotation3D, [in] ProjectionMatrix, [out] ViewMatrix)
zox_system(CameraFollow2DSystem, EcsOnUpdate, [none] CameraFollower2D, [in] FreeRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D)
spawn_camera_base_prefab(world);
spawn_prefab_free_camera(world);
spawn_camera2D_follower_prefab(world);
zoxel_end_module(Cameras)

//   todo: Custom name for namespaces used in flecs
//       const char* nm_zoxel_cameras = "Zoxel.cameras";
//       zox_module(world, cameras, nm_zoxel_cameras);

#endif