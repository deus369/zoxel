#ifndef zoxel_ui_elements
#define zoxel_ui_elements

zox_declare_tag(Label)            // UI extras, make extra ui module?
zox_declare_tag(Button)           //! A generic ui button for clicking.
zox_declare_tag(Window)           //! A ui window.
zox_declare_tag(Header)           //! A ui window header.
zox_declare_tag(CloseButton)      //! A ui window close button.
#include "prefabs/label.c"
#include "prefabs/label_background.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
#include "util/header.c"
#include "util/window.c"
#include "prefabs/ui_list.c"
#include "systems/button_click_sound_system.c"
#include "systems/element_drag_system.c"
#include "fun/button_event_close_window.c"

void spawn_prefabs_elements(ecs_world_t *world) {
    spawn_prefab_label(world);
    spawn_prefab_label_background(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
    spawn_prefab_ui_list(world);
}

zox_begin_module(Elements)
zox_define_tag(Label)
zox_define_tag(Button)
zox_define_tag(Window)
zox_define_tag(Header)
zox_define_tag(CloseButton)
zox_system(ElementDragSystem, EcsPostLoad, [none] Header, [in] DragableState, [in] DraggingDelta, [in] ParentLink)
zox_system(ButtonClickSoundSystem, EcsPostUpdate, [none] Button, [in] ClickableState)
zoxel_end_module(Elements)

#endif