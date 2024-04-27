#ifndef zoxel_ui_core
#define zoxel_ui_core

// zoxel_settings
#include "settings/settings.c"
// zoxel_declare_components
zox_declare_tag(Element)
zox_declare_tag(Element3D)
zox_declare_tag(Canvas)
zox_declare_tag(ElementRaycaster)
zox_declare_tag(ElementBillboard)
zox_declare_tag(BoundToCanvas)
zox_component_byte(InitializeEntityMesh)
zox_component_byte(NavigatorState)
zox_component_byte(ElementFontSize)
zox_component_float(ElementBar)
zox_time_component(NavigatorTimer)
zox_component_int2(CanvasPosition)
zox_component_int2(ElementMargins)
zox_component_float2(Anchor)
zox_component_float2(AnchorSize)
zox_component_float2(ElementBarSize)
zox_component(UITrail, float3)
zox_component(CanvasLink, ecs_entity_t)
zox_component(UIHolderLink, ecs_entity_t)
zox_function_component(ClickEvent, void, ecs_world_t*, ecs_entity_t)
zox_entities_component(ElementLinks)
zox_component_byte(HeaderHeight)
// zoxel_include_util
#include "util/ui_prefab_util.c"
#include "util/ui_transform_util.c"
#include "util/anchor_util.c"
#include "util/prefab_util_world_ui.c"
#include "util/element_render_util.c"
#include "util/click_util.c"
#include "util/toggle_util.c"
#include "util/resize_util.c"
#include "util/world_ui_util.c"
// zoxel_include_prefabs
#include "prefabs/canvas.c"
#include "prefabs/element.c"
#include "prefabs/element_basic.c"
#include "prefabs/element_invisible.c"
#include "prefabs/element_world.c"
#include "prefabs/element_world_child.c"
#include "prefabs/canvas_overlay.c"
// zoxel_declare_systems
#include "systems/button_click_event_system.c"
#include "systems/element_raycast_system.c"
#include "systems/element_selected_system.c"
#include "systems/element_activate_system.c"
#include "systems/element_navigation_system.c"
#include "systems/element_position_system.c"
#include "systems/element_mesh2D_system.c"
#include "systems/element_mesh3D_system.c"
#include "systems/billboard_system.c"
#include "systems/ui_trail_system.c"
#include "systems/element_bar_system.c"
#include "systems/canvas_resize_system.c"

void spawn_prefabs_ui_core(ecs_world_t *world) {
    spawn_prefab_canvas(world);
    spawn_prefab_element(world);
    spawn_prefab_element_basic(world);
    spawn_prefab_element_invisible(world);
    spawn_prefab_element3D(world);
    spawn_prefab_element3D_child(world);
    spawn_prefab_canvas_overlay(world);
}

zox_begin_module(UICore)
// zoxel_define_components
zox_define_tag(Element)
zox_define_tag(Element3D)
zox_define_tag(Canvas)
zox_define_tag(ElementRaycaster)
zox_define_tag(ElementBillboard)
zox_define_tag(BoundToCanvas)
zox_define_component_byte(InitializeEntityMesh)
zox_define_component_byte(NavigatorState)
zox_define_component_byte(ElementFontSize)
zox_define_component_float(ElementBar)
zox_define_component_int2(CanvasPosition)
zox_define_component_int2(ElementMargins)
zox_define_component_float2(Anchor)
zox_define_component_float2(AnchorSize)
zox_define_component_float2(ElementBarSize)
zox_define_component(NavigatorTimer)
zox_define_component(UITrail)
zox_define_component(CanvasLink)
zox_define_component(UIHolderLink)
zox_define_component(ClickEvent)
zox_define_entities_component(ElementLinks)
zox_define_component_byte(HeaderHeight)
// zoxel_define_filters
zox_filter(ui_query, [none] Element, [in] CanvasPosition, [in] PixelSize, [in] Layer2D, [in] RenderDisabled, [out] SelectState)
zox_filter(pixel_positions_query, [none] Element, [in] PixelPosition, [none] ParentLink, [none] Anchor, [none] CanvasLink, [none] Position2D, [none] CanvasPosition)
// zoxel_define_systems
#ifdef zoxel_inputs
zox_system_ctx(ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [in] DeviceMode, [out] RaycasterTarget)
zox_system(ElementActivateSystem, EcsPostUpdate, [in] DeviceLinks, [in] DeviceMode, [in] RaycasterTarget, [out] RaycasterResult, [out] ClickingEntity)
zox_system(ElementNavigationSystem, EcsPostUpdate, [in] DeviceLinks, [in] DeviceMode, [out] NavigatorState, [out] NavigatorTimer, [out] RaycasterTarget)
#endif
zox_system_ctx(ElementPositionSystem, EcsPreUpdate, pixel_positions_query, [none] Element, [in] PixelPosition, [in] ParentLink, [in] Anchor, [in] CanvasLink, [out] Position2D, [out] CanvasPosition)
zox_system(ElementSelectedSystem, EcsOnUpdate, [none] Element, [in] SelectState, [out] Brightness)
zox_system(BillboardSystem, zox_transforms_stage, [none] ElementBillboard, [in] CameraLink, [in] Position3D, [out] Rotation3D)
zox_system(UITrailSystem, zox_transforms_stage, [in] UIHolderLink, [in] UITrail, [out] Position3D)
zox_system(ElementBarSystem, EcsOnUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children)
if (!headless) {
    zox_system_1(Element2DMeshSystem, main_thread_pipeline, [none] Element, [in] PixelSize, [in] MeshAlignment, [in] CanvasLink, [out] InitializeEntityMesh, [out] MeshDirty, [out] MeshVertices2D, [out] MeshGPULink, [out] TextureGPULink, [out] UvsGPULink, [none] !Element3D)
    zox_system_1(Element3DMeshSystem, main_thread_pipeline, [none] Element3D, [in] PixelSize, [in] CanvasLink, [out] InitializeEntityMesh, [out] MeshDirty, [out] GenerateTexture,  [out] MeshGPULink, [out] UvsGPULink, [out] ColorsGPULink, [out] TextureGPULink)
    zox_system_1(ButtonClickEventSystem, main_thread_pipeline, [none] Element, [in] ClickEvent, [out] ClickState)
}
zox_system(CanvasResizeSystem, EcsOnUpdate, [in] CameraLink, [in] Children, [in] cameras.ScreenToCanvas, [out] PixelSize, [none] Canvas)
zoxel_end_module(UICore)

#endif
