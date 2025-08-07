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

entity prefab_label;
entity prefab_button;
entity prefab_close_button;
entity prefab_icon;
entity prefab_frame;
entity prefab_label_background;
entity prefab_scrollbar_front;
entity prefab_scrollbar;
entity prefab_list;
entity prefab_ui_list;
entity prefab_header;
entity prefab_body;
entity prefab_window_invisible;
entity prefab_window;
entity prefab_elementbar2D;
entity prefab_elementbar2D_front;
entity prefab_icon_mouse_follow;
entity prefab_icon_overlay;
entity prefab_handle;
entity prefab_slider;

// todo: make a more advanced 'element' prefab, alott of these still use prefab_element
//  - element_selectable, element_clickable, element_draggable

void spawn_prefabs_elements(ecs *world) {
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
    prefab_window_invisible = spawn_prefab_window_invisible(world, prefab_layout2);
    prefab_window = spawn_prefab_window(world, prefab_element_textured);
    // lists
    prefab_ui_list = spawn_prefab_ui_list(world, prefab_window);
    prefab_list = spawn_prefab_ui_list(world, prefab_element_textured);
}