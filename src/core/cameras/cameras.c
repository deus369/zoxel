#ifndef zoxel_cameras
#define zoxel_cameras

#define max_cameras 16
const float camera_far_distance = 6000;
int main_cameras_count = 1;
ecs_entity_t main_cameras[max_cameras];
ecs_entity_t ui_cameras[1];
zoxel_declare_tag(Camera)
zoxel_declare_tag(CameraFollower2D)  // a tag for a camera that follows a Character2D
zoxel_declare_tag(UICamera)
zoxel_component(ProjectionMatrix, float4x4) //! Used for the cameras frustrum.
zoxel_component(ViewMatrix, float4x4)       //! Used with all the materials to render the scene.
zoxel_component(ScreenDimensions, int2)     //! Has dimensions of the camera viewport screen. Used to calculate a camera frustrum.
zoxel_component(ScreenPosition, int2)
zoxel_component(FieldOfView, float)         //! Used to calculate a camera frustrum.
zoxel_component(CameraNearDistance, float)
zoxel_component(CameraLink, ecs_entity_t)   //! A link to a Camera
zoxel_component(CameraTarget, ecs_entity_t) //! A link to a Camera Target entity.
zoxel_byte_component(FreeRoam)             //! Used to free roam a camera.
#include "prefabs/camera_base.c"
#include "prefabs/camera2D.c"
#include "prefabs/ui_camera.c"
#include "util/main_camera.c"
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"
#include "systems/camera2D_follow_system.c"

void CamerasImport(ecs_world_t *world) {
    zoxel_module(Cameras)
    zoxel_define_tag(Camera)
    zoxel_define_tag(CameraFollower2D) // Until fix is found. \todo Fix this, readd it back here where it belongs.
    zoxel_define_tag(UICamera)
    zoxel_define_component(CameraLink)
    zoxel_define_component(CameraTarget)
    zoxel_define_component(ProjectionMatrix)
    zoxel_define_component(ViewMatrix)
    zoxel_define_component(ScreenDimensions)
    zoxel_define_component(ScreenPosition)
    zoxel_define_component(FieldOfView)
    zoxel_define_component(CameraNearDistance)
    zoxel_define_component(FreeRoam)
    zoxel_system_main_thread(world, ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [in] CameraNearDistance, [out] ProjectionMatrix)
    zoxel_system(world, ViewMatrixSystem, EcsOnUpdate, [in] Position3D, [in] Rotation3D, [in] ProjectionMatrix, [out] ViewMatrix)
    zoxel_system(world, CameraFollow2DSystem, EcsOnUpdate, [none] CameraFollower2D, [in] FreeRoam, [in] CameraTarget, [out] Position3D, [out] Rotation3D)
    spawn_camera_base_prefab(world);
    spawn_camera2D_follower_prefab(world);
}

/**
*   Custom name for namespace?
*       const char* nm_zoxel_cameras = "Zoxel.cameras";
*       zoxel_module(world, cameras, nm_zoxel_cameras);
*/
#endif