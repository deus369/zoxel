#include "element_raycast_system.c"
#include "element_active_system.c"
#include "element_selected_system.c"
#include "element_position_system.c"
#include "element_mesh2D_system.c"
#include "elementbar2D_system.c"
#include "canvas_resize_system.c"
#include "canvas_stack_system.c"
#include "window_layer_system.c"
#include "element_render_system.c"
#include "click_sound_system.c"
#include "render_texture_render_system.c"
zox_increment_system_with_reset_extra(ClickState, zox_click_state_trigger_clicked, zox_click_state_clicked_idle, zox_click_state_trigger_released, zox_click_state_idle)
zox_increment_system_with_reset_extra(SelectState, zox_select_state_trigger_selected, zox_select_state_selected, zox_select_state_trigger_deselect, zox_select_state_deselected_idle)
#include "inputs/button_click_event_system.c"
#include "inputs/dragger_end_system.c"
#include "inputs/element_navigation_system.c"
#include "inputs/mouse_element_system.c"
#include "inputs/device_click_system.c"
#include "inputs/zevice_click_system.c"

void define_systems_elements_core(ecs_world_t *world) {
    zox_filter(ui_query, [none] Element, [in] CanvasPosition, [in] PixelSize, [in] Layer2D, [in] RenderDisabled, [none] Selectable)
    zox_filter(pixel_positions_query, [none] Element, [in] PixelPosition, [none] ParentLink, [none] Anchor, [none] CanvasLink, [none] Position2D, [none] CanvasPosition)
    zox_system_ctx(ElementRaycastSystem, EcsOnUpdate, ui_query, [in] Raycaster, [in] DeviceLink, [out] RaycasterTarget, [out] WindowRaycasted)
    // inputs
    zox_system(ZeviceClickSystem, EcsPostUpdate, [in] DeviceLink, [in] RaycasterTarget, [in] WindowRaycasted, [out] RaycasterResult, [out] ClickingEntity, [out] WindowTarget, [none] inputs.Zevice)
    zox_system(DeviceClickSystem, EcsPostUpdate, [in] PlayerLink, [in] RaycasterTarget, [in] WindowRaycasted, [in] Children, [out] RaycasterResult, [out] ClickingEntity, [out] WindowTarget, [none] inputs.Device)

    zox_system(ElementNavigationSystem, EcsPostUpdate, [in] DeviceLinks, [in] DeviceMode, [out] NavigatorState, [out] NavigatorTimer, [out] RaycasterTarget)
    // EcsPreUpdate pixel_positions_query,
    zox_system_ctx(ElementPositionSystem, EcsOnLoad, pixel_positions_query, [in] PixelPosition, [in] PixelSize, [in] ParentLink, [in] Anchor, [in] CanvasLink, [out] Position2D, [out] CanvasPosition, [none] Element)
    zox_system(CanvasStackSystem, EcsOnLoad, [in] Children, [out] WindowToTop, [out] WindowsLayers, [out] WindowsCount, [none] Canvas)
    zox_system(WindowLayerSystem, EcsOnLoad, [in] SetWindowLayer, [in] CanvasLink, [in] Children, [out] WindowLayer, [out] Layer2D, [none] Window)
    zox_system(ElementSelectedSystem, EcsOnUpdate, [none] Element, [in] SelectState, [out] Brightness)
    zox_system(ElementActiveSystem, EcsOnUpdate, [in] ActiveState, [out] Brightness, [none] Element, [none] !SelectState)
    zox_system(MouseElementSystem, zox_transforms_stage, [in] ZeviceLink, [in] Anchor, [in] CanvasLink, [out] PixelPosition, [none] MouseElement)
    zox_system(Elementbar2DSystem, EcsOnUpdate, [in] ElementBar, [in] ElementBarSize, [in] Children, [in] PixelSize, [none] MeshVertices2D)
    if (!headless) {
        zox_system_1(ButtonClickEventSystem, zox_pip_mainthread, [in] ClickEvent, [in] ClickState, [out] Clicker, [none] Element)
        // EcsOnLoad - zox_pip_mainthread
        zox_system_1(Element2DMeshSystem, EcsOnLoad, [none] Element, [in] PixelSize, [in] MeshAlignment, [in] CanvasLink, [out] InitializeElement, [out] MeshDirty, [out] MeshVertices2D, [out] MeshGPULink, [out] TextureGPULink, [out] UvsGPULink) // , [none] !Element3D)
    }
    zox_system(CanvasResizeSystem, EcsOnUpdate, [in] CameraLink, [in] Children, [in] cameras.ScreenToCanvas, [out] PixelSize, [none] Canvas)
    // all ui
    zox_render2D_system(RenderTextureRenderSystem, [in] TransformMatrix, [in] Layer2D, [in] RenderDisabled, [in] MeshGPULink, [in] UvsGPULink, [in] TextureGPULink, [none] cameras.RenderTexture)
    zox_render2D_system(ElementRenderSystem, [in] Position2D, [in] Rotation2D, [in] Scale1D, [in] Layer2D,  [in] RenderDisabled, [in] Brightness, [in] Alpha, [in] MeshGPULink, [in] UvsGPULink, [in] TextureGPULink, [none] ElementRender, [none] !cameras.RenderTexture)
    // healthbars
    zox_system_1(ClickSoundSystem, zox_pip_mainthread, [in] ClickState, [none] ClickMakeSound)
    zox_system(DraggerEndSystem, EcsPostLoad, [out] DraggableState, [out] DraggerLink, [out] DraggingDelta)
    // zox_define_reset_system_pip(ClickState, EcsOnLoad)
    zox_define_increment_system(ClickState, EcsOnLoad)
    zox_define_increment_system(SelectState, EcsOnLoad)
}
