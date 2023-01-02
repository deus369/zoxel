#ifndef zoxel_lines
#define zoxel_lines

// tags
zoxel_declare_tag(Line)
// components
zoxel_component(LineThickness, float)
#include "lines2D/lines2D.c"
#include "lines3D/lines3D.c"

//! Lines Module.
void LinesImport(ecs_world_t *world)
{
    zoxel_module(Lines)
    zoxel_define_tag(Line)
    zoxel_define_component(LineThickness)
    zoxel_import_module(Lines2D)
    zoxel_import_module(Lines3D)
}
#endif