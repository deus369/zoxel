//! Use this until i can support multiple cameras
//! Spawn a Camera
/**
 * Give the camera a Transform, a ViewMatrix.
 * Animate it moving a little upwards.
*/
ecs_entity_t mainCamera;

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

ecs_entity_t SpawnCamera(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions)
{
    ecs_entity_t newCamera = ecs_new_w_pair(world, EcsIsA, cameraPrefab);
    ecs_set(world, newCamera, Position, { position });
    ecs_set(world, newCamera, Rotation, { rotation });
    // ecs_set(world, newCamera, ViewMatrix, { float4x4_zero() });    // malloc(16 * 4)
    ecs_set(world, newCamera, ScreenDimensions, { { screenDimensions.x, screenDimensions.y } });
    // this part will be hard
    // ecs_set(world, newCamera, ViewMatrix, { 0 });
    printf("Spawned Camera [%lu]\n", (long unsigned int) newCamera);
    return newCamera;
}

void SpawnMainCamera(int2 screenDimensions)
{
    float3 spawnPosition = { 0, -0.0f, 1.2 };
    // imagine this is a forward rotation
    // float4 flipRotation = quaternion_from_euler( (float3) { 0, 180 * degreesToRadians, 0 });
    // float4 flipRotation = quaternion_from_euler( (float3) { 0, 0 * degreesToRadians, 0 });
    float4 spawnRotation = quaternion_identity(); // quaternion_from_euler( (float3) { 0 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
    // spawnRotation = quaternion_rotate(flipRotation, spawnRotation);
    mainCamera = SpawnCamera(world, spawnPosition, spawnRotation, screenDimensions);
}

//! Used for testing cleanup
void DestroyMainCamera()
{
    ecs_delete(world, mainCamera);
}