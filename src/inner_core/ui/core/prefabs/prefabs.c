ecs_entity_t prefab_canvas;
ecs_entity_t prefab_canvas_overlay;
ecs_entity_t prefab_element;
ecs_entity_t prefab_element_invisible;
ecs_entity_t prefab_element_basic;
ecs_entity_t prefab_element3D;
ecs_entity_t prefab_element3D_child;

#include "canvas.c"
#include "element.c"
#include "element_basic.c"
#include "element_invisible.c"
#include "element_world.c"
#include "element_world_child.c"
#include "canvas_overlay.c"

void spawn_prefabs_ui_core(ecs_world_t *world) {
    prefab_canvas = spawn_prefab_canvas(world);
    prefab_element = spawn_prefab_element(world);
    prefab_element_basic = spawn_prefab_element_basic(world);
    prefab_element_invisible = spawn_prefab_element_invisible(world);
    prefab_element3D = spawn_prefab_element3D(world);
    prefab_element3D_child = spawn_prefab_element3D_child(world);
    prefab_canvas_overlay = spawn_prefab_canvas_overlay(world);
}
