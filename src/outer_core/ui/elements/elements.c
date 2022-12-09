#ifndef zoxel_ui_elements
#define zoxel_ui_elements

// tags
// UI extras, make extra ui module?
ECS_DECLARE(Label);
//! A generic ui button for clicking.
ECS_DECLARE(Button);
//! A ui window.
ECS_DECLARE(Window);
//! A ui window header.
ECS_DECLARE(Header);
//! A ui window close button.
ECS_DECLARE(CloseButton);
ECS_DECLARE(PlayGameButton);
ECS_DECLARE(ExitGameButton);
// components
// util
// prefabs
#include "prefabs/label.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
// util
#include "util/header.c"
#include "util/window.c"
// systems
#include "systems/button_click_sound_system.c"
#include "systems/window_close_system.c"
#include "systems/header_drag_system.c"

//! The Elements contains various things I can use in my uis.
void ElementsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Elements);
    ECS_TAG_DEFINE(world, Label);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, Window);
    ECS_TAG_DEFINE(world, Header);
    ECS_TAG_DEFINE(world, CloseButton);
    ECS_TAG_DEFINE(world, PlayGameButton);
    ECS_TAG_DEFINE(world, ExitGameButton);
    // systems
    zoxel_system(world, ButtonClickSoundSystem, EcsPostUpdate, [none] Button, [in] ClickableState);
    zoxel_system(world, WindowCloseSystem, EcsOnValidate, [none] CloseButton, [in] ClickableState);
    zoxel_system(world, HeaderDragSystem, EcsPostUpdate, [none] Header, [in] DragableState,
        [in] DraggingDelta, [in] ParentLink);
    // prefabs
    spawn_prefab_label(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
}
#endif