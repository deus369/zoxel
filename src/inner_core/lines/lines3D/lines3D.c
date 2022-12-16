#ifndef zoxel_lines3D
#define zoxel_lines3D

// Tags
ECS_DECLARE(Line3D);
// components
//! The two points in a line, held in a float4.
// zoxel_component(LineData, float6);

//! Lines2D Module.
void Lines3DImport(ecs_world_t *world)
{
    ECS_MODULE(world, Lines3D);
    ECS_TAG_DEFINE(world, Line3D);
    // ECS_COMPONENT_DEFINE(world, LineData);
    // systems
    // prefabs
}
#endif