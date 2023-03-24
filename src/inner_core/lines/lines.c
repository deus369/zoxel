#ifndef zoxel_lines
#define zoxel_lines

zoxel_declare_tag(Line)
zoxel_component(LineThickness, float)
#include "lines2D/lines2D.c"
#include "lines3D/lines3D.c"

void LinesImport(ecs_world_t *world) {
    zoxel_log("         > importing lines\n");
    zoxel_module(Lines)
    zoxel_define_tag(Line)
    zoxel_define_component(LineThickness)
    zoxel_import_module(Lines2D)
    zoxel_import_module(Lines3D)
    zoxel_log("         > imported lines\n");
}
#endif