#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Tags
ECS_DECLARE(Camera);
ECS_DECLARE(CameraFollower2D);  // a tag for a camera that follows a Character2D
// Data
#include "Components/ViewMatrix.c"
#include "Components/ScreenDimensions.c"
#include "Components/FieldOfView.c"
// Prefabs
#include "Prefabs/Camera2D.c"
// Systems
#include "Systems/CameraSpawnSystem.c"
#include "Systems/ViewMatrixSystem.c"

// Remember it will destroy the prefab ones too... *facepalm*

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    ECS_TAG_DEFINE(world, Camera);
    ECS_TAG_DEFINE(world, CameraFollower2D); // Until fix is found. \todo Fix this, readd it back here where it belongs.
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_SYSTEM_DEFINE(world, ViewMatrixSystem, EcsOnUpdate, [in] ScreenDimensions, [in] FieldOfView, [out] ViewMatrix);
    SpawnCameraPrefab(world);
    ecs_add(world, cameraPrefab, CameraFollower2D);
}

void SpawnMainCamera(int2 screenDimensions)
{
    float3 spawnPosition = { 0, -0.0f, 1.2 };
    // imagine this is a forward rotation
    // float4 flipRotation = quaternion_from_euler( (float3) { 0, 180 * degreesToRadians, 0 });
    // float4 flipRotation = quaternion_from_euler( (float3) { 0, 0 * degreesToRadians, 0 });
    float4 spawnRotation = quaternion_identity(); // quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
    // spawnRotation = quaternion_rotate(flipRotation, spawnRotation);
    SpawnCamera(world, spawnPosition, spawnRotation, screenDimensions);
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void ResizeCameras(int width, int height)
{
    if (!mainCamera || !ecs_is_alive(world, mainCamera))
    {
        return;
    }
    ScreenDimensions *screenDimensions = ecs_get_mut(world, mainCamera, ScreenDimensions);
    screenDimensions->value.x = width;
    screenDimensions->value.y = height;
    ecs_modified(world, mainCamera, ScreenDimensions);
}

const float4x4 GetMainCameraViewMatrix()
{
    if (!mainCamera || !ecs_is_alive(world, mainCamera))
    {
        return float4x4_zero();
    }
    const ViewMatrix *viewMatrix = ecs_get(world, mainCamera, ViewMatrix);
    return viewMatrix->value;
}
#endif