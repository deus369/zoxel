ecs_entity_t prefab_menu_start;
ecs_entity_t prefab_menu_paused;
ecs_entity_t prefab_main_menu;
ecs_entity_t prefab_menu_options;
ecs_entity_t fps_display_prefab;
ecs_entity_t fps_display;
ecs_entity_t prefab_game_debug_label;
ecs_entity_t prefab_quad_count_label;
ecs_entity_t prefab_virtual_joystick;
ecs_entity_t prefab_virtual_joystick_pointer;
ecs_entity_t prefab_tooltip;
ecs_entity_t prefab_icon_frame_taskbar;
ecs_entity_t prefab_taskbar;
ecs_entity_t prefab_device_gizmo;ecs_entity_t prefab_menu_game;
ecs_entity_t prefab_menu_game_touch;
ecs_entity_t zoxel_main_menu;

#include "menu_start.c"
#include "menu_main.c"
#include "menu_options.c"
#include "menu_paused.c"
#include "fps_display.c"
#include "quad_count_label.c"
#include "game_debug_label.c"
#include "virtual_joystick_pointer.c"
#include "virtual_joystick.c"
#include "tooltip.c"
#include "icon_frame_taskbar.c"
#include "taskbar.c"
#include "device_gizmo.c"
#include "crosshair.c"
#include "menu_game_touch.c"
#include "menu_game.c"

void spawn_prefabs_game_ui(ecs_world_t *world) {
    prefab_menu_start = spawn_prefab_main_start(world, prefab_ui_list);
    prefab_main_menu = spawn_prefab_main_menu(world);
    prefab_menu_paused = spawn_prefab_pause_ui(world);
    prefab_menu_options = spawn_prefab_options_ui(world);
    spawn_prefab_fps_display(world);
    spawn_prefab_quad_count_label(world);
    spawn_prefab_game_debug_label(world, prefab_label_background);
    prefab_virtual_joystick_pointer = spawn_prefab_virtual_joystick_pointer(world);
    prefab_virtual_joystick = spawn_prefab_virtual_joystick(world);
    prefab_tooltip = spawn_prefab_tooltip(world, prefab_label_background);
    prefab_icon_frame_taskbar = spawn_prefab_icon_frame_taskbar(world, prefab_icon_frame);
    prefab_taskbar = spawn_prefab_taskbar(world, prefab_element);
    prefab_device_gizmo = spawn_prefab_device_gizmo(world, prefab_icon);
    prefab_menu_game = spawn_prefab_menu_game(world, prefab_element_invisible);
    prefab_menu_game_touch = spawn_prefab_menu_game_touch(world, prefab_element_invisible);
}
