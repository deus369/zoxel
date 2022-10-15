#ifndef Zoxel_Cameras
#define Zoxel_Cameras

// Tags
ECS_DECLARE(Camera);
// Data
#include "Components/ViewMatrix.c"
#include "Components/ScreenDimensions.c"
#include "Components/FieldOfView.c"
// Systems
#include "Systems/CameraSpawnSystem.c"
#include "Systems/ViewMatrixSystem.c"

void CamerasImport(ecs_world_t *world)
{
    ECS_MODULE(world, Cameras);
    ECS_TAG_DEFINE(world, Camera);
    ECS_COMPONENT_DEFINE(world, ViewMatrix);
    ECS_COMPONENT_DEFINE(world, ScreenDimensions);
    ECS_COMPONENT_DEFINE(world, FieldOfView);
    ECS_SYSTEM_DEFINE(world, ViewMatrixSystem, EcsOnUpdate, ViewMatrix, ScreenDimensions, FieldOfView);
    // ViewMatrixSetSystem - add observer for on set
    ecs_observer_init(world, &(ecs_observer_desc_t) {
        .filter.terms = { { ecs_id(ViewMatrix) } },
        .events = EcsOnSet,
        .callback = ViewMatrixSetSystem
    });
    // Add on destroy observer
    ecs_observer_init(world, &(ecs_observer_desc_t){
        .filter.terms = { { ecs_id(ViewMatrix) } },
        .events = EcsOnRemove,   // EcsOnSet
        .callback = ViewMatrixDisposeSystem
    });
    // EcsOnSet, calculate view frustrum when screen dimensions change
}

void InitializeCameras(ecs_world_t *world)
{
    InitializeCameraSpawnSystem(world);
}

void SpawnMainCamera(int2 screenDimensions)
{
    float3 spawnPosition = { 0, 0, 0 };
    float4 spawnRotation = { 0, 0, 0, 1 };
    SpawnCamera(world, spawnPosition, spawnRotation, screenDimensions);
}

void ResizeCameras(int width, int height)
{
    if (!ecs_is_alive(world, mainCamera))
    {
        return;
    }
    ScreenDimensions *screenDimensions = ecs_get_mut(world, mainCamera, ScreenDimensions);
    screenDimensions->value.x = width;
    screenDimensions->value.y = height; //{ width, height };
    ecs_modified(world, mainCamera, ScreenDimensions);
}

const float* GetMainCameraViewMatrix()
{
    if (!ecs_is_alive(world, mainCamera))
    {
        return NULL;
    }
    const ViewMatrix *viewMatrix = ecs_get(world, mainCamera, ViewMatrix);
    return viewMatrix->value;
    // glUniformMatrix4fv(gl_view_matrix, 1, GL_FALSE, (const GLfloat*) viewMatrix);
}

#endif