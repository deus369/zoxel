#ifndef zoxel_ui_elements
#define zoxel_ui_elements

// tags
// UI extras, make extra ui module?
ECS_DECLARE(Label);
// components
// util
// prefabs
#include "prefabs/label.c"

//! The UI contains ways to interact with 2D objects.
void UIElementsImport(ecs_world_t *world)
{
    ECS_MODULE(world, UIElements);
    ECS_TAG_DEFINE(world, Label);
    // prefabs
    spawn_prefab_label(world);
}
#endif