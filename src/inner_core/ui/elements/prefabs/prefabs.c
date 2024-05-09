ecs_entity_t label_prefab;
ecs_entity_t prefab_button;
ecs_entity_t header_prefab;
ecs_entity_t prefab_close_button;
ecs_entity_t prefab_label_background;
ecs_entity_t prefab_elementbar3D;
ecs_entity_t prefab_elementbar3D_front;
ecs_entity_t prefab_elementbar2D;
ecs_entity_t prefab_elementbar2D_front;
ecs_entity_t prefab_scrollbar_front;
ecs_entity_t prefab_scrollbar;
ecs_entity_t prefab_ui_list;
ecs_entity_t prefab_window;

#include "label.c"
#include "label_background.c"
#include "button.c"
#include "header.c"
#include "window.c"
#include "scrollbar_front.c"
#include "scrollbar.c"
#include "ui_list.c"
#include "elementbar2D_front.c"
#include "elementbar2D.c"
#include "elementbar3D_front.c"
#include "elementbar3D.c"

void spawn_prefabs_elements(ecs_world_t *world) {
    spawn_prefab_label(world);
    spawn_prefab_label_background(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
    spawn_prefab_button_close(world);
    spawn_prefab_scrollbar(world);
    spawn_prefab_scrollbar_front(world);
    spawn_prefab_ui_list(world);
    spawn_prefab_elementbar2D(world);
    spawn_prefab_elementbar2D_front(world);
    spawn_prefab_elementbar3D(world);
    spawn_prefab_elementbar3D_front(world);
}
