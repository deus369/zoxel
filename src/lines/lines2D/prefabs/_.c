#include "line2D.c"
#include "ui_line2D.c"
#include "ui_line2D_temp.c"

void spawn_prefabs_lines2D(ecs_world_t *world) {
    spawn_prefab_line2D(world);
    spawn_prefab_line2D_temp(world);
    spawn_prefab_ui_line2D(world);
    spawn_prefab_ui_line2D_temp(world);
}