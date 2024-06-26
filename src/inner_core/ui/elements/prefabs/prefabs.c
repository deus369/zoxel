ecs_entity_t prefab_label;
ecs_entity_t prefab_button;
ecs_entity_t prefab_close_button;
ecs_entity_t prefab_icon;
ecs_entity_t prefab_icon_frame;
ecs_entity_t prefab_label_background;
ecs_entity_t prefab_scrollbar_front;
ecs_entity_t prefab_scrollbar;
ecs_entity_t prefab_ui_list;
ecs_entity_t prefab_header;
ecs_entity_t prefab_body;
ecs_entity_t prefab_window_invisible;
ecs_entity_t prefab_window;
ecs_entity_t prefab_elementbar3D;
ecs_entity_t prefab_elementbar3D_front;
ecs_entity_t prefab_elementbar2D;
ecs_entity_t prefab_elementbar2D_front;

#include "label.c"
#include "label_background.c"
#include "button.c"
#include "close_button.c"
#include "icon.c"
#include "icon_frame.c"
#include "header.c"
#include "body.c"
#include "window.c"
#include "scrollbar_front.c"
#include "scrollbar.c"
#include "ui_list.c"
#include "elementbar2D_front.c"
#include "elementbar2D.c"
#include "elementbar3D_front.c"
#include "elementbar3D.c"

void spawn_prefabs_elements(ecs_world_t *world) {
    prefab_label = spawn_prefab_label(world);
    prefab_label_background = spawn_prefab_label_background(world);
    prefab_button = spawn_prefab_button(world);
    prefab_window_invisible = spawn_prefab_window_invisible(world);
    prefab_window = spawn_prefab_window(world); // todo: add visible components onto invisible window
    prefab_header = spawn_prefab_header(world);
    prefab_body = spawn_prefab_body(world, prefab_element);
    prefab_close_button = spawn_prefab_button_close(world, prefab_button);
    prefab_scrollbar = spawn_prefab_scrollbar(world);
    prefab_scrollbar_front = spawn_prefab_scrollbar_front(world);
    prefab_ui_list = spawn_prefab_ui_list(world);
    prefab_elementbar2D = spawn_prefab_elementbar2D(world);
    prefab_elementbar2D_front = spawn_prefab_elementbar2D_front(world);
    prefab_elementbar3D = spawn_prefab_elementbar3D(world, prefab_element3D);
    prefab_elementbar3D_front = spawn_prefab_elementbar3D_front(world, prefab_element3D_child);
    prefab_icon = spawn_prefab_icon(world, prefab_element);
    prefab_icon_frame  = spawn_prefab_icon_frame(world, prefab_element);
}
