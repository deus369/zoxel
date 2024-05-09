ecs_entity_t prefab_menu_paused;
ecs_entity_t prefab_main_menu;
ecs_entity_t prefab_menu_options;
ecs_entity_t fps_display_prefab;
ecs_entity_t fps_display;
ecs_entity_t prefab_game_debug_label;
ecs_entity_t prefab_quad_count_label;
ecs_entity_t prefab_virtual_joystick;
// ecs_entity_t virtual_joystick;  // reference for now
ecs_entity_t prefab_virtual_joystick_pointer;

#include "menu_main.c"
#include "menu_options.c"
#include "menu_paused.c"
#include "fps_display.c"
#include "quad_count_label.c"
#include "game_debug_label.c"
#include "virtual_joystick_pointer.c"
#include "virtual_joystick.c"

void spawn_prefabs_game_ui(ecs_world_t *world) {
    spawn_prefab_main_menu(world);
    spawn_prefab_fps_display(world);
    spawn_prefab_pause_ui(world);
    spawn_prefab_options_ui(world);
    spawn_prefab_quad_count_label(world);
    spawn_prefab_game_debug_label(world);
    spawn_prefab_virtual_joystick_pointer(world);
    spawn_prefab_virtual_joystick(world);
}
