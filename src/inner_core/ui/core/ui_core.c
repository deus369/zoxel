#ifndef zoxel_ui_core
#define zoxel_ui_core

// 0 | EcsPostUpdate
#define ui_mesh_pipeline 0
long int element_mesh_system_id;
ecs_entity_t main_canvas;
zox_declare_tag(Element)                  //! A basic tag for a UI Element.
zox_declare_tag(Canvas)
zox_declare_tag(ElementRaycaster)
zox_component(CanvasPixelPosition, int2)
zox_component(Anchor, float2)             //! An anchor, used to get base position using canvas
zox_component(CanvasLink, ecs_entity_t)   //! A link to a canvas
zox_byte_component(InitializeEntityMesh)
zox_time_component(NavigatorTimer)
zox_function_component(ClickEvent, void, ecs_world_t*, ecs_entity_t)
#include "util/ui_prefab_util.c"
#include "util/ui_util.c"
#include "util/anchor_util.c"
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "systems/button_click_event_system.c"
#include "systems/element_raycast_system.c"
#include "systems/element_selected_system.c"
#include "systems/element_activate_system.c"
#include "systems/element_navigation_system.c"
#include "systems/element_position_system.c"
#include "systems/element_mesh_system.c"

zox_begin_module(UICore)
zox_define_tag(Element)
zox_define_tag(Canvas)
zox_define_tag(ElementRaycaster)
zox_define_component(CanvasPixelPosition)
zox_define_component(Anchor)
zox_define_component(CanvasLink)
zox_define_component(ClickEvent)
zox_define_component(InitializeEntityMesh)
zox_define_component(NavigatorTimer)
spawn_prefab_canvas(world);
spawn_prefab_element(world);
// filters
zox_filter(ui_query, [none] Element, [in] CanvasPixelPosition, [in] PixelSize, [in] Layer2D, [out] SelectableState)
zox_filter(pixel_positions_query, [none] Element, [in] PixelPosition,
    [none] ParentLink, [none] Anchor, [none] CanvasLink, [none] Position2D, [none] CanvasPixelPosition)
// systems
zox_system_ctx(ElementPositionSystem, EcsPreUpdate, pixel_positions_query, [none] Element, [in] PixelPosition,
    [in] ParentLink, [in] Anchor, [in] CanvasLink, [out] Position2D, [out] CanvasPixelPosition)
zox_system_ctx(ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [in] DeviceMode, [out] RaycasterTarget)
zox_system(ElementSelectedSystem, EcsOnUpdate, [none] Element, [in] SelectableState, [out] Brightness)
if (!headless) {
    #ifdef zoxel_inputs
        zox_system(ElementActivateSystem, EcsPostUpdate, [in] DeviceLinks, [in] RaycasterTarget)
        zox_system(ElementNavigationSystem, EcsPostUpdate, [in] DeviceLinks, [out] NavigatorTimer, [out] RaycasterTarget)
    #endif
    zox_system_1(ElementMeshSystem, ui_mesh_pipeline, [none] Element, [in] PixelSize, [in] CanvasLink, [out] InitializeEntityMesh, [out] MeshDirty, [out] GenerateTexture)
    element_mesh_system_id = ecs_id(ElementMeshSystem);
}
zox_system(ButtonClickEventSystem, EcsPreStore, [none] Element, [in] ClickableState, [in] ClickEvent)
zoxel_end_module(UICore)

// \todo Display a UI Element anchored, with a pixel position.
// \todo Change colour when ray hits a button.
//! \todo When resizing, reposition UIs.
//      - should i use a resize event in the window?
// completely 2D ui? 3D canvas + 3D transforms?
// canvas: still uses 2D posti

#endif