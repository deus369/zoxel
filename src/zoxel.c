#ifndef zoxel
#define zoxel

// =-= Zoxel =-=
#include "core/core.c"
#include "inner_core/inner_core.c"
#include "outer_core/outer_core.c"
#include "gameplay/gameplay.c"
#include "space/space.c"

void ZoxelImport(ecs_world_t *world)
{
    ECS_MODULE(world, Zoxel);
    ECS_IMPORT(world, Core);
    ECS_IMPORT(world, InnerCore);
    ECS_IMPORT(world, OuterCore);
    ECS_IMPORT(world, Gameplay);
    ECS_IMPORT(world, Space);
}
#endif