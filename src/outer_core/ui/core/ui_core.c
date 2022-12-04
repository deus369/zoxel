#ifndef zoxel_ui_core
#define zoxel_ui_core

// #define debug_ui_positioning

//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?

// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

ecs_entity_t main_canvas;
// tags
//! A basic tag for a UI Element.
ECS_DECLARE(Element);
ECS_DECLARE(Canvas);
ECS_DECLARE(ElementRaycaster);
// components
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
// systems
#include "systems/element_raycast_system.c"
#include "systems/element_selected_system.c"
#include "systems/element_activate_system.c"
// render initialize systems
#include "systems/element_mesh_system.c"

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
    ECS_COMPONENT_DEFINE(world, CanvasPixelPosition);
    ECS_COMPONENT_DEFINE(world, Anchor);
    ECS_COMPONENT_DEFINE(world, CanvasLink);
    ECS_COMPONENT_DEFINE(world, ElementLayer);
    // Systems
    zoxel_filter(ui_query, world, [none] Element, [in] CanvasPixelPosition, [in] PixelSize, [in] ElementLayer, [out] SelectableState);
    zoxel_system_ctx(world, ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [out] RaycasterTarget);
    zoxel_system(world, ElementSelectedSystem, EcsOnUpdate, [out] Element, [in] SelectableState, [out] Brightness);
    // make Activator?
    zoxel_system(world, ElementActivateSystem, EcsOnUpdate, [in] Mouse, [in] RaycasterTarget);
    zoxel_system_main_thread(world, ElementMeshSystem, EcsOnLoad, [none] Element,
        [in] EntityInitialize, [in] PixelSize, [in] CanvasLink);
    // ClicableState - reset system
    // destroy window
    // children - destroy children - hook
    // prefabs
    spawn_prefab_canvas(world);
    spawn_prefab_element(world);
}
// zoxel_system_ctx(world, ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster);
// zoxel_system(world, ElementSelectedSystem, EcsOnUpdate, [out] Element, [in] ClickableState, [out] Brightness);
#endif