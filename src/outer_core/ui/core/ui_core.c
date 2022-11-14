#ifndef zoxel_ui_core
#define zoxel_ui_core

//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?

// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

// tags
//! A basic tag for a UI Element.
ECS_DECLARE(Element);
ECS_DECLARE(Canvas);
ECS_DECLARE(ElementRaycaster);
// UI extras, make extra ui module?
ECS_DECLARE(Button);
// A ui window!
ECS_DECLARE(Window);
// A ui window!
ECS_DECLARE(Header);
// components
zoxel_component(PixelPosition, int2);
zoxel_component(PixelSize, int2);
zoxel_component(CanvasPixelPosition, int2);
//! A 2D Layer for a entity. (make generic 2D component instead of just UI)
zoxel_component(ElementLayer, unsigned char);
//! An anchor, used to get base position using canvas
zoxel_component(Anchor, float2);
//! A link to a canvas.
zoxel_component(CanvasLink, ecs_entity_t);
// util
#include "util/ui_util.c"
// prefabs
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "prefabs/button.c"
#include "prefabs/header.c"
#include "prefabs/window.c"
// systems
#include "systems/element_raycast_system.c"
#include "systems/element_selected_system.c"

//! The UI contains ways to interact with 2D objects.
/**
 * \todo Display a UI Element anchored, with a pixel position.
 * \todo Change colour when ray hits a button.
*/
void UICoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, UICore);
    ECS_TAG_DEFINE(world, Element);
    ECS_TAG_DEFINE(world, Canvas);
    ECS_TAG_DEFINE(world, ElementRaycaster);
    ECS_TAG_DEFINE(world, Button);
    ECS_TAG_DEFINE(world, Window);
    ECS_TAG_DEFINE(world, Header);
    ECS_COMPONENT_DEFINE(world, PixelPosition);
    ECS_COMPONENT_DEFINE(world, PixelSize);
    ECS_COMPONENT_DEFINE(world, CanvasPixelPosition);
    ECS_COMPONENT_DEFINE(world, Anchor);
    ECS_COMPONENT_DEFINE(world, CanvasLink);
    ECS_COMPONENT_DEFINE(world, ElementLayer);
    // Systems
    zoxel_filter(ui_query, world, [none] Element, [in] CanvasPixelPosition, [in] PixelSize, [in] ElementLayer, [out] SelectableState);
    zoxel_system_ctx(world, ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [out] RaycasterTarget);
    
    zoxel_system(world, ElementSelectedSystem, EcsOnUpdate, [out] Element, [in] SelectableState, [out] Brightness);
   
    //zoxel_system_ctx(world, ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster);
    //zoxel_system(world, ElementSelectedSystem, EcsOnUpdate, [out] Element, [in] ClickableState, [out] Brightness);

    // prefabs
    spawn_prefab_canvas(world);
    spawn_prefab_element(world);
    spawn_prefab_window(world);
    spawn_prefab_button(world);
}
#endif