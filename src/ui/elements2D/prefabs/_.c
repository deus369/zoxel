#include "label.c"
#include "label_background.c"
#include "button.c"
#include "icon_overlay.c"
#include "icon.c"
#include "frame.c"
#include "close_button.c"
#include "header.c"
#include "body.c"
#include "window.c"
#include "window_invisible.c"
#include "scrollbar_front.c"
#include "scrollbar.c"
#include "handle.c"
#include "slider.c"
#include "ui_list.c"
#include "elementbar2D_front.c"
#include "elementbar2D.c"
#include "mouse_follow_icon.c"

ecs_entity_t prefab_label;
ecs_entity_t prefab_button;
ecs_entity_t prefab_close_button;
ecs_entity_t prefab_icon;
ecs_entity_t prefab_frame;
ecs_entity_t prefab_label_background;
ecs_entity_t prefab_scrollbar_front;
ecs_entity_t prefab_scrollbar;
ecs_entity_t prefab_ui_list;
ecs_entity_t prefab_header;
ecs_entity_t prefab_body;
ecs_entity_t prefab_window_invisible;
ecs_entity_t prefab_window;
ecs_entity_t prefab_elementbar2D;
ecs_entity_t prefab_elementbar2D_front;
ecs_entity_t prefab_icon_mouse_follow;
ecs_entity_t prefab_icon_overlay;
ecs_entity_t prefab_handle;
ecs_entity_t prefab_slider;

// todo: make a more advanced 'element' prefab, alott of these still use prefab_element
//  - element_selectable, element_clickable, element_draggable

void spawn_prefabs_elements(ecs_world_t *world) {
    // elements
    prefab_label = spawn_prefab_label(world, prefab_zext);
    prefab_label_background = spawn_prefab_label_background(world, prefab_zext);
    prefab_button = spawn_prefab_button(world, prefab_element_textured);
    // statbars
    prefab_elementbar2D = spawn_prefab_elementbar2D(world);
    prefab_elementbar2D_front = spawn_prefab_elementbar2D_front(world);
    // icons
    prefab_icon = spawn_prefab_icon(world, prefab_element_textured);
    prefab_frame  = spawn_prefab_frame(world, prefab_element_textured);
    prefab_icon_overlay = spawn_prefab_icon_overlay(world, prefab_element_textured);
    // scrollbars
    prefab_scrollbar = spawn_prefab_scrollbar(world);
    prefab_scrollbar_front = spawn_prefab_scrollbar_front(world, prefab_element_textured);
    // slider
    prefab_handle = spawn_prefab_handle(world, prefab_element_textured);
    prefab_slider = spawn_prefab_slider(world, prefab_element_textured);
    // mouse
    prefab_icon_mouse_follow = spawn_prefab_icon_mouse_follow(world, prefab_element_textured);
    // panel
    prefab_body = spawn_prefab_body(world, prefab_element_textured);
    // header
    prefab_header = spawn_prefab_header(world, prefab_element_textured);
    prefab_close_button = spawn_prefab_button_close(world, prefab_button);
    // windows
    prefab_window_invisible = spawn_prefab_window_invisible(world, prefab_layout2D);
    prefab_window = spawn_prefab_window(world, prefab_element_textured);
    // lists
    prefab_ui_list = spawn_prefab_ui_list(world, prefab_window);
}