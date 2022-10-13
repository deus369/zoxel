// Rendering
#include "Components/Brightness.c"
ECS_COMPONENT_DECLARE(Brightness);
#include "Components/Mesh.c"
ECS_COMPONENT_DECLARE(Mesh);
// Systems
#include "Systems/Render2DSystem.c"

//! The Rendering Core Sub Module.
/**
*   \todo CPU Meshes?
*/
void InitializeRenderingCore(ecs_world_t *world)
{
    // printf("Initializing Rendering Core.");
    ECS_COMPONENT_DEFINE(world, Brightness);
    ECS_COMPONENT_DEFINE(world, Mesh);
    ECS_SYSTEM_DEFINE(world, Render2DSystem, EcsOnStore, Position2D, Rotation2D, Scale2D, Brightness);
}