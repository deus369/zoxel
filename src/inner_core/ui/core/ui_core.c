#ifndef zox_mod_ui_core
#define zox_mod_ui_core

zox_declare_tag(Element)
zox_declare_tag(Element3D)
zox_declare_tag(Canvas)
zox_declare_tag(ElementRaycaster)
zox_declare_tag(ElementBillboard)
zox_declare_tag(BoundToCanvas)
zox_declare_tag(CanvasOverlay)
zox_declare_tag(Window)
zox_declare_tag(WindowRaycastTarget)
zox_declare_tag(ElementRender)
zox_declare_tag(MouseElement)
zox_component_byte(Layer2D)
zox_component_byte(NavigatorState)
zox_component_byte(ElementFontSize)
zox_component_float(ElementBar)
zox_component_float2(ElementBarSize)
zox_component_double(NavigatorTimer)
zox_component_int2(CanvasPosition)
zox_component_int2(ElementMargins)
zox_component_float2(Anchor)
zox_component_float2(AnchorSize)
zox_component_float3(UITrail)
zox_component_entity(CanvasLink)
zox_component_entity(UIHolderLink)
zox_component_byte(HeaderHeight)
zox_function_component(ClickEvent, void, ecs_world_t*, ecs_entity_t, ecs_entity_t)
zox_entities_component(ElementLinks)
zox_component_entity(WindowRaycasted)
zox_component_entity(WindowTarget)
zox_component_entity(WindowToTop)
zox_component_byte(WindowsLayers)
zox_component_byte(WindowsCount)
zox_component_byte(SetWindowLayer)
zox_component_byte(WindowLayer)
zox_component_byte(ElementLayer)
zox_component_byte(InitializeElement)
zox_declare_tag(ClickMakeSound)
zox_declare_tag(Selectable)
zox_declare_tag(Clickable)
zox_declare_tag(Dragable)
zox_component_byte(SelectState)
zox_component_byte(ActiveState)
zox_component_byte(ClickState)
zox_component_byte(DraggableState)
zox_component_int2(DraggingDelta)
zox_component_int4(DraggableLimits)
zox_component_entity(Clicker)
zox_component_entity(ClickingEntity)
zox_component_entity(DraggerLink)
zox_component_entity(DraggedLink)
zox_component_entity(ElementLink)
#include "data/tooltip_event_data.c"
zox_function_component(TooltipEvent, void, ecs_world_t*, const TooltipEventData*)
#include "data/settings.c"
#include "data/click_states.c"
#include "data/select_states.c"
#include "data/canvas_spawn_data.c"
#include "data/parent_spawn_data.c"
#include "data/element_spawn_data.c"
#include "util/canvas_util.c"
#include "util/ui_prefab_util.c"
#include "util/ui_transform_util.c"
#include "util/anchor_util.c"
#include "util/prefab_util_world_ui.c"
#include "util/element_render_util.c"
#include "util/click_util.c"
#include "util/toggle_util.c"
#include "util/resize_util.c"
#include "util/world_ui_util.c"
#include "util/layers.c"
#include "util/canvas_fading.c"
#include "prefabs/prefabs.c"
#include "systems/button_click_event_system.c"
#include "systems/element_raycast_system.c"
#include "systems/element_active_system.c"
#include "systems/element_selected_system.c"
#include "systems/element_click_system.c"
#include "systems/element_navigation_system.c"
#include "systems/element_position_system.c"
#include "systems/element_mesh2D_system.c"
#include "systems/element_mesh3D_system.c"
#include "systems/ui_trail_system.c"
#include "systems/element_bar_system.c"
#include "systems/canvas_resize_system.c"
#include "systems/canvas_stack_system.c"
#include "systems/window_layer_system.c"
#include "systems/element_render_system.c"
#include "systems/element3D_render_system.c"
#include "systems/click_sound_system.c"
#include "systems/dragger_end_system.c"
#include "systems/render_texture_render_system.c"
#include "systems/mouse_element_system.c"
// zox_reset_system(ClickState)
zox_increment_system_with_reset_extra(ClickState, zox_click_state_trigger_clicked, zox_click_state_clicked_idle, zox_click_state_trigger_released, zox_click_state_idle)
zox_increment_system_with_reset_extra(SelectState, zox_select_state_trigger_selected, zox_select_state_selected, zox_select_state_trigger_deselect, zox_select_state_deselected_idle)

zox_begin_module(UICore)
zox_define_tag(Element)
zox_define_tag(Element3D)
zox_define_tag(Canvas)
zox_define_tag(ElementRaycaster)
zox_define_tag(BoundToCanvas)
zox_define_tag(CanvasOverlay)
zox_define_tag(Window)
zox_define_tag(WindowRaycastTarget)
zox_define_tag(ElementRender)
zox_define_tag(MouseElement)
zox_define_component_byte(Layer2D)
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
zox_define_component_entity(CanvasLink)
zox_define_component(UIHolderLink)
zox_define_component(ClickEvent)
zox_define_component(TooltipEvent)
zox_define_entities_component(ElementLinks)
zox_define_component_byte(HeaderHeight)
zox_define_component_entity(WindowRaycasted)
zox_define_component_entity(WindowTarget)
zox_define_component_entity(WindowToTop)
zox_define_component_byte(WindowsLayers)
zox_define_component_byte(WindowsCount)
zox_define_component_byte(SetWindowLayer)
zox_define_component_byte(WindowLayer)
zox_define_component_byte(ElementLayer)
zox_define_component_byte(InitializeElement)
zox_define_tag(ClickMakeSound)
zox_define_tag(Selectable)
zox_define_tag(Clickable)
zox_define_tag(Dragable)
zox_define_component_byte(SelectState)
zox_define_component_byte(ActiveState)
zox_define_component_byte(ClickState)
zox_define_component_entity(ClickingEntity)
zox_define_component_entity(Clicker)
zox_define_component_entity(ElementLink)
zox_define_component_byte(DraggableState)
zox_define_component_int2(DraggingDelta)
zox_define_component_int4(DraggableLimits)
zox_define_component_entity(DraggerLink)       // the what that drags
zox_define_component_entity(DraggedLink)       // the who gets dragged
zox_filter(ui_query, [none] Element, [in] CanvasPosition, [in] PixelSize, [in] Layer2D, [in] RenderDisabled, [none] Selectable)
zox_filter(pixel_positions_query, [none] Element, [in] PixelPosition, [none] ParentLink, [none] Anchor, [none] CanvasLink, [none] Position2D, [none] CanvasPosition)
zox_system_ctx(ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [in] DeviceLink, [out] RaycasterTarget, [out] WindowRaycasted)
zox_system(ElementClickSystem, EcsPostUpdate, [in] DeviceLink, [in] RaycasterTarget, [in] WindowRaycasted, [out] RaycasterResult, [out] ClickingEntity, [out] WindowTarget)
zox_system(ElementNavigationSystem, EcsPostUpdate, [in] DeviceLinks, [in] DeviceMode, [out] NavigatorState, [out] NavigatorTimer, [out] RaycasterTarget)
// EcsPreUpdate pixel_positions_query,
zox_system_ctx(ElementPositionSystem, EcsOnLoad, pixel_positions_query, [in] PixelPosition, [in] PixelSize, [in] ParentLink, [in] Anchor, [in] CanvasLink, [out] Position2D, [out] CanvasPosition, [none] Element)
zox_system(CanvasStackSystem, EcsOnLoad, [in] Children, [out] WindowToTop, [out] WindowsLayers, [out] WindowsCount, [none] Canvas)
zox_system(WindowLayerSystem, EcsOnLoad, [in] SetWindowLayer, [in] CanvasLink, [in] Children, [out] WindowLayer, [out] Layer2D, [none] Window)
zox_system(ElementSelectedSystem, EcsOnUpdate, [none] Element, [in] SelectState, [out] Brightness)
zox_system(ElementActiveSystem, EcsOnUpdate, [in] ActiveState, [out] Brightness, [none] Element, [none] !SelectState)
zox_system(MouseElementSystem, zox_transforms_stage, [in] ZeviceLink, [in] Anchor, [in] CanvasLink, [out] PixelPosition, [none] MouseElement)
zox_system(UITrailSystem, zox_transforms_stage, [in] UIHolderLink, [in] UITrail, [out] Position3D)
zox_system(ElementBarSystem, EcsOnUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children)
if (!headless) {
    zox_system_1(ButtonClickEventSystem, zox_pip_mainthread, [in] ClickEvent, [in] ClickState, [out] Clicker, [none] Element)
    // EcsOnLoad
    zox_system_1(Element2DMeshSystem, zox_pip_mainthread, [none] Element, [in] PixelSize, [in] MeshAlignment, [in] CanvasLink, [out] InitializeElement, [out] MeshDirty, [out] MeshVertices2D, [out] MeshGPULink, [out] TextureGPULink, [out] UvsGPULink, [none] !Element3D)
    zox_system_1(Element3DMeshSystem, zox_pip_mainthread, [none] Element3D, [in] PixelSize, [in] CanvasLink, [out] InitializeElement, [out] MeshDirty, [out] GenerateTexture,  [out] MeshGPULink, [out] UvsGPULink, [out] ColorsGPULink, [out] TextureGPULink)
}
zox_system(CanvasResizeSystem, EcsOnUpdate, [in] CameraLink, [in] Children, [in] cameras.ScreenToCanvas, [out] PixelSize, [none] Canvas)
// all ui
zox_render2D_system(RenderTextureRenderSystem, [in] TransformMatrix, [in] Layer2D, [in] RenderDisabled, [in] MeshGPULink, [in] UvsGPULink, [in] TextureGPULink, [none] cameras.RenderTexture)
zox_render2D_system(ElementRenderSystem, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Layer2D,  [in] RenderDisabled, [in] Brightness, [in] Alpha, [in] MeshGPULink, [in] UvsGPULink, [in] TextureGPULink, [in] MeshDirty, [none] ElementRender, [none] !cameras.RenderTexture)
// healthbars
zox_render3D_system(Element3DRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] TextureGPULink, [in] RenderDisabled, [none] rendering.core.SingleMaterial)
zox_system_1(ClickSoundSystem, zox_pip_mainthread, [in] ClickState, [none] ClickMakeSound)
zox_system(DraggerEndSystem, EcsPostLoad, [out] DraggableState, [out] DraggerLink, [out] DraggingDelta)
// zox_define_reset_system_pip(ClickState, EcsOnLoad)
zox_define_increment_system(ClickState, EcsOnLoad)
zox_define_increment_system(SelectState, EcsOnLoad)
spawn_prefabs_ui_core(world);
zoxel_end_module(UICore)

#endif
