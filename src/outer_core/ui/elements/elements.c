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
// components
// util
// prefabs
#include "prefabs/label.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
// systems
#include "systems/window_close_system.c"

//! The Elements contains various things I can use in my uis.
void UIElementsImport(ecs_world_t *world)
{
    ECS_MODULE(world, UIElements);
    ECS_TAG_DEFINE(world, Label);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, CloseButton);
    ECS_TAG_DEFINE(world, Window);
    ECS_TAG_DEFINE(world, Header);
    // systems
    zoxel_system(world, WindowCloseSystem, EcsOnValidate, [none] CloseButton, [in] ClickableState);
    // prefabs
    spawn_prefab_label(world);
    spawn_prefab_button(world);
    spawn_prefab_window(world);
    spawn_prefab_header(world);
}
#endif