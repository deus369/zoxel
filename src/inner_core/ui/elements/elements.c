#ifndef zoxel_ui_elements
#define zoxel_ui_elements

zoxel_declare_tag(Label)            // UI extras, make extra ui module?
zoxel_declare_tag(Button)           //! A generic ui button for clicking.
zoxel_declare_tag(Window)           //! A ui window.
zoxel_declare_tag(Header)           //! A ui window header.
zoxel_declare_tag(CloseButton)      //! A ui window close button.
#include "prefabs/label.c"
#include "prefabs/label_background.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
#include "util/header.c"
#include "util/window.c"
#include "systems/button_click_sound_system.c"
#include "systems/header_drag_system.c"
#include "fun/button_event_close_window.c"

zoxel_begin_module(Elements)
zoxel_define_tag(Label)
zoxel_define_tag(Button)
zoxel_define_tag(Window)
zoxel_define_tag(Header)
zoxel_define_tag(CloseButton)
zox_system(ButtonClickSoundSystem, EcsPreStore, [none] Button, [in] ClickableState)   // EcsOnUpdate
zox_system(HeaderDragSystem, EcsPostLoad, [none] Header, [in] DragableState, [in] DraggingDelta, [in] ParentLink)
spawn_prefab_label(world);
spawn_prefab_label_background(world);
spawn_prefab_button(world);
spawn_prefab_window(world);
spawn_prefab_header(world);
zoxel_end_module(Elements)

#endif