ecs_entity_t prefab_canvas;
ecs_entity_t prefab_canvas_overlay;
ecs_entity_t prefab_element;
ecs_entity_t prefab_element_world_child;
ecs_entity_t prefab_element_world;
ecs_entity_t prefab_element_invisible;
ecs_entity_t prefab_element_basic;

#include "canvas.c"
#include "element.c"
#include "element_basic.c"
#include "element_invisible.c"
#include "element_world.c"
#include "element_world_child.c"
#include "canvas_overlay.c"

void spawn_prefabs_ui_core(ecs_world_t *world) {
    spawn_prefab_canvas(world);
    spawn_prefab_element(world);
    spawn_prefab_element_basic(world);
    spawn_prefab_element_invisible(world);
    spawn_prefab_element3D(world);
    spawn_prefab_element3D_child(world);
    spawn_prefab_canvas_overlay(world);
}
