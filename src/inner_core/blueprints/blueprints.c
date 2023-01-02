#ifndef zoxel_blueprints
#define zoxel_blueprints

// tags per entity
ECS_DECLARE(Blueprint);
ECS_DECLARE(Bluenode);
// components
// prefabs
// systems

void BlueprintsImport(ecs_world_t *world)
{
    zoxel_module(Blueprints)
    ECS_TAG_DEFINE(world, Blueprint);
    ECS_TAG_DEFINE(world, Bluenode);
}
#endif