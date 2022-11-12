#ifndef zoxel_ui_core
#define zoxel_ui_core

//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?

// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

// tags
//! A basic tag for a UI Element.
ECS_DECLARE(Element);
ECS_DECLARE(Selectable);
ECS_DECLARE(Clickable);
ECS_DECLARE(Canvas);
ECS_DECLARE(ElementRaycaster);
// UI extras, make extra ui module?
ECS_DECLARE(Button);
// A ui window!
ECS_DECLARE(Window);
// components
zoxel_component(PixelPosition, int2);
zoxel_component(PixelSize, int2);
//! An anchor, used to get base position using canvas
zoxel_component(Anchor, float2);
zoxel_component(CanvasLink, ecs_entity_t);
// util
#include "util/ui_util.c"
// prefabs
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "prefabs/button.c"
#include "prefabs/window.c"
// systems
#include "systems/element_raycast_system.c"

//! The UI contains ways to interact with 2D objects.
/**
 * \todo Display a UI Element anchored, with a pixel position.
 * \todo Change colour when ray hits a button.
*/
void UICoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, UICore);
    ECS_TAG_DEFINE(world, Element);
    ECS_TAG_DEFINE(world, Selectable);
    ECS_TAG_DEFINE(world, Clickable);
    ECS_TAG_DEFINE(world, Canvas);
    ECS_TAG_DEFINE(world, ElementRaycaster);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, Window);
    ECS_COMPONENT_DEFINE(world, PixelPosition);
    ECS_COMPONENT_DEFINE(world, PixelSize);
    ECS_COMPONENT_DEFINE(world, Anchor);
    ECS_COMPONENT_DEFINE(world, CanvasLink);
    // Systems
    zoxel_system(world, ElementRaycastSystem, EcsOnUpdate, [none] ElementRaycaster);
    // prefabs
    spawn_prefab_canvas(world);
    spawn_prefab_element(world);
    spawn_prefab_window(world);
    spawn_prefab_button(world);
    spawn_canvas(world, screenDimensions);
}
#endif