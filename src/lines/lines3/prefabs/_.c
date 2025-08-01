ecs_entity_t prefab_line3D;
ecs_entity_t prefab_temporary_line3D;
ecs_entity_t prefab_cube_lines;

#include "line3D.c"
#include "temporary_line3D.c"
#include "cube_lines.c"
#include "arrow.c"

void spawn_prefabs_lines3D(ecs_world_t *world) {
    prefab_line3D = spawn_prefab_line3D(world);
    prefab_temporary_line3D = spawn_prefab_temporary_line3D(world);
    prefab_cube_lines = spawn_prefab_cube_lines(world);
}