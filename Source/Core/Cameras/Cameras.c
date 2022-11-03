#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Custom name for namespace?
// const char* nm_zoxel_cameras = "Zoxel.Cameras";

// -=- Tags -=-
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
// -=- Components -=-
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
// -=- Prefabs -=-
#include "Prefabs/CameraBase.c"
#include "Prefabs/Camera2D.c"
// -=- Util -=-
#include "Util/MainCamera.c"
// -=- Systems -=-
#include "Systems/ProjectionMatrixSystem.c"
#include "Systems/ViewMatrixSystem.c"

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    // zoxel_module(world, Cameras, nm_zoxel_cameras);
    // -=- Tags -=-
    ECS_TAG_DEFINE(world, Camera);
    ECS_TAG_DEFINE(world, CameraFollower2D); // Until fix is found. \todo Fix this, readd it back here where it belongs.
    // -=- Components -=-
    ECS_COMPONENT_DEFINE(world, CameraLink);
    ECS_COMPONENT_DEFINE(world, ProjectionMatrix);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_COMPONENT_DEFINE(world, FreeRoam);
    // -=- Systems -=-
    ECS_SYSTEM_DEFINE(world, ProjectionMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [out] ProjectionMatrix);
    zoxel_system(world, ViewMatrixSystem, EcsOnUpdate, [in] Position, [in] Rotation, [in] ProjectionMatrix, [out] ViewMatrix);
    // -=- Prefabs -=-
    SpawnCameraBasePrefab(world);
    SpawnCameraPrefab(world);
}
#endif