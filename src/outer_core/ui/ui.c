#ifndef zoxel_ui
#define zoxel_ui

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
// components
//! An anchor, used to get base position using canvas
zoxel_component(Anchor, unsigned char);
zoxel_component(PixelPosition, int2);
zoxel_component(CanvasLink, ecs_entity_t);
// prefabs
#include "prefabs/element.c"
#include "prefabs/button.c"
#include "prefabs/canvas.c"
// systems
#include "systems/element_raycast_system.c"

//! The UI contains ways to interact with 2D objects.
/**
 * \todo Display a UI Element anchored, with a pixel position.
 * \todo Change colour when ray hits a button.
*/
void UIImport(ecs_world_t *world)
{
    ECS_MODULE(world, UI);
    ECS_TAG_DEFINE(world, Element);
    ECS_TAG_DEFINE(world, Selectable);
    ECS_TAG_DEFINE(world, Clickable);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, Canvas);
    ECS_TAG_DEFINE(world, ElementRaycaster);
    ECS_COMPONENT_DEFINE(world, Anchor);
    ECS_COMPONENT_DEFINE(world, PixelPosition);
    ECS_COMPONENT_DEFINE(world, CanvasLink);
    // Systems
    zoxel_system(world, ElementRaycastSystem, EcsOnUpdate, [none] ElementRaycaster);
    // prefabs
    spawn_element_prefab(world);
    // test, spawn canvas, element
}
#endif