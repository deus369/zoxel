#ifndef zoxel_ui_elements
#define zoxel_ui_elements

zoxel_declare_tag(Label)            // UI extras, make extra ui module?
zoxel_declare_tag(Button)           //! A generic ui button for clicking.
zoxel_declare_tag(Window)           //! A ui window.
zoxel_declare_tag(Header)           //! A ui window header.
zoxel_declare_tag(CloseButton)      //! A ui window close button.
zoxel_declare_tag(PlayGameButton)
zoxel_declare_tag(ExitGameButton)
#include "prefabs/label.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
#include "util/header.c"
#include "util/window.c"
#include "systems/button_click_sound_system.c"
#include "systems/window_close_system.c"
#include "systems/header_drag_system.c"

void ElementsImport(ecs_world_t *world) {
    zoxel_module(Elements)
    zoxel_define_tag(Label)
    zoxel_define_tag(Button)
    zoxel_define_tag(Window)
    zoxel_define_tag(Header)
    zoxel_define_tag(CloseButton)
    zoxel_define_tag(PlayGameButton)
    zoxel_define_tag(ExitGameButton)
    zoxel_system(world, ButtonClickSoundSystem, EcsOnUpdate, [none] Button, [in] ClickableState);
    zoxel_system(world, WindowCloseSystem, EcsPostUpdate, [none] CloseButton, [in] ClickableState);
    zoxel_system(world, HeaderDragSystem, EcsPostLoad, [none] Header, [in] DragableState, [in] DraggingDelta, [in] ParentLink);
    spawn_prefab_label(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
}
#endif