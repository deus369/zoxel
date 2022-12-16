#ifndef zoxel_lines
#define zoxel_lines

// tags
ECS_DECLARE(Line);
// components
zoxel_component(LineThickness, float);
#include "lines2D/lines2D.c"
#include "lines3D/lines3D.c"

//! Lines Module.
void LinesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Lines);
    ECS_TAG_DEFINE(world, Line);
    ECS_COMPONENT_DEFINE(world, LineThickness);
    ECS_IMPORT(world, Lines2D);
    ECS_IMPORT(world, Lines3D);
}
#endif