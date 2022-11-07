#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Custom name for namespace?
// const char* nm_zoxel_cameras = "Zoxel.cameras";

// -=- Tags -=-
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
// -=- components -=-
//! Used for the cameras frustrum.
zoxel_component(ProjectionMatrix, float4x4);
//! Used with all the materials to render the scene.
zoxel_component(ViewMatrix, float4x4);
//! Has dimensions of the camera viewport screen. Used to calculate a camera frustrum.
zoxel_component(ScreenDimensions, int2);
//! Used to calculate a camera frustrum.
zoxel_component(FieldOfView, float);
//! A link to a Camera
zoxel_component(CameraLink, ecs_entity_t);
//! Used to free roam a camera.
zoxel_component(FreeRoam, bool);
// -=- prefabs -=-
#include "prefabs/camera_base.c"
#include "prefabs/camera2D.c"
// -=- util -=-
#include "util/main_camera.c"
// -=- systems -=-
#include "systems/projection_matrix_system.c"
#include "systems/view_matrix_system.c"

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, cameras);
    // zoxel_module(world, cameras, nm_zoxel_cameras);
    // -=- Tags -=-
    ECS_TAG_DEFINE(world, Camera);
    ECS_TAG_DEFINE(world, CameraFollower2D); // Until fix is found. \todo Fix this, readd it back here where it belongs.
    // -=- components -=-
    ECS_COMPONENT_DEFINE(world, CameraLink);
    ECS_COMPONENT_DEFINE(world, ProjectionMatrix);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_COMPONENT_DEFINE(world, FreeRoam);
    // -=- systems -=-
    ECS_SYSTEM_DEFINE(world, ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [out] ProjectionMatrix);
    zoxel_system(world, ViewMatrixSystem, EcsOnUpdate, [in] Position, [in] Rotation, [in] ProjectionMatrix, [out] ViewMatrix);
    // -=- prefabs -=-
    spawn_camera_base_prefab(world);
    spawn_camera_prefab(world);
}
#endif