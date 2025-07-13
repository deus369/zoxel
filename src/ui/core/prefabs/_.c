ecs_entity_t prefab_canvas;
ecs_entity_t prefab_layout2D;
ecs_entity_t prefab_element_basic;
ecs_entity_t prefab_element_textured;
ecs_entity_t prefab_render_texture;
ecs_entity_t prefab_canvas_overlay;

#include "canvas.c"
#include "layout2D.c"
#include "element_basic.c"
#include "element_textured.c"
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
    // just has transform and layouts2D
    prefab_layout2D = spawn_prefab_layout2D(world);
    // has a texture also
    prefab_element_basic = spawn_prefab_element_basic(world, prefab_layout2D);
    // has a frame texture
    prefab_element_textured = spawn_prefab_element_textured(world, prefab_element_basic);
    // more stuffs
    prefab_render_texture = spawn_prefab_render_texture(world, prefab_element_basic);
    prefab_canvas_overlay = spawn_prefab_canvas_overlay(world);
    // linking
    if (prefab_player) {
        prefabs_add_ui_to_raycaster(world, prefab_player);
        prefabs_add_ui_to_player(world, prefab_player);
    }
    if (prefab_device) {
        prefabs_add_ui_to_raycaster(world, prefab_device);
    }
    if (prefab_zevice_pointer) {
        prefabs_add_ui_to_raycaster(world, prefab_zevice_pointer);
    }
}