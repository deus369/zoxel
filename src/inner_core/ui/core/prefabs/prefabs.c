ecs_entity_t prefab_canvas;
ecs_entity_t prefab_canvas_overlay;
ecs_entity_t prefab_element;
ecs_entity_t prefab_element_invisible;
ecs_entity_t prefab_element_basic;
ecs_entity_t prefab_element3D;
ecs_entity_t prefab_element3D_child;
ecs_entity_t prefab_render_texture;

#include "canvas.c"
#include "element.c"
#include "element_basic.c"
#include "element_invisible.c"
#include "element_world.c"
#include "element_world_child.c"
#include "canvas_overlay.c"
#include "element_texture.c"
#include "render_texture.c"

void prefabs_add_ui_to_player(ecs_world_t *world, const ecs_entity_t e) {
    // Player -> Devices
    zox_prefab_set(e, DeviceMode, { 0 })
    zox_prefab_set(e, DeviceModeDirty, { 0 })
    zox_prefab_add(e, DeviceLinks)
    zox_prefab_add(e, ElementLinks)
    zox_prefab_set(e, CanvasLink, { 0 })
    // this is all UI interaction
    zox_prefab_set(e, NavigatorState, { 0 })
    zox_prefab_set(e, NavigatorTimer, { 0 })
}

void prefabs_add_ui_to_raycaster(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, WindowRaycasted, { 0 })
    zox_prefab_set(e, WindowTarget, { 0 })
    zox_prefab_set(e, ClickingEntity, { 0 })

}

void spawn_prefabs_ui_core(ecs_world_t *world) {
    prefab_canvas = spawn_prefab_canvas(world);
#if defined(zox_mod_players)
    zox_prefab_set(prefab_canvas, PlayerLink, { 0 })
#endif
    prefab_element = spawn_prefab_element(world);
    prefab_element_basic = spawn_prefab_element_basic(world);
    prefab_element_invisible = spawn_prefab_element_invisible(world);
    prefab_element3D = spawn_prefab_element3D(world);
    prefab_element3D_child = spawn_prefab_element3D_child(world);
    prefab_canvas_overlay = spawn_prefab_canvas_overlay(world);
    prefabs_add_ui_to_player(world, prefab_player);
    prefab_render_texture = spawn_prefab_render_texture(world);
    prefabs_add_ui_to_raycaster(world, prefab_device);
    prefabs_add_ui_to_raycaster(world, prefab_zevice_pointer);
    prefabs_add_ui_to_raycaster(world, prefab_player);
}
