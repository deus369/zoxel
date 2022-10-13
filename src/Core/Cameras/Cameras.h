#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Tags
ECS_DECLARE(Camera);

// Data
#include "Components/ViewMatrix.c"

// Systems
#include "Systems/CameraSpawnSystem.c"

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    ECS_TAG_DEFINE(world, Camera);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
}

void InitializeCameras(ecs_world_t *world)
{
    InitializeCameraSpawnSystem(world);
    float3 spawnPosition = { 0, 0, 0 };
    float4 spawnRotation = { 0, 0, 0, 1 };
    SpawnCamera(world, spawnPosition, spawnRotation);
}

#endif