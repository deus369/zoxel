#ifndef zoxel_lines
#define zoxel_lines

zox_declare_tag(Line)
zox_component(LineThickness, float)
#include "lines2D/lines2D.c"
#include "lines3D/lines3D.c"

void initialize_lines(ecs_world_t *world) {
    initialize_lines2D(world);
    initialize_lines3D(world);
}

void spawn_prefabs_lines(ecs_world_t *world) {
    spawn_prefabs_lines2D(world);
    spawn_prefabs_lines3D(world);
}

zox_begin_module(Lines)
zox_define_tag(Line)
zox_define_component(LineThickness)
zox_import_module(Lines2D)
zox_import_module(Lines3D)
zoxel_end_module(Lines)

#endif
