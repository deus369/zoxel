#include "element_raycast_system.c"
#include "element_active_system.c"
#include "element_selected_system.c"

#include "layouts2D/canvas_resize_system.c"
#include "layouts2D/element_position_system.c"
#include "layouts2D/canvas_stack_system.c"
#include "layouts2D/window_layer_system.c"

#include "rendering/element_mesh2D_system.c"
#include "rendering/render_texture_render_system.c"
#include "rendering/element_render_system.c"

#include "inputs/button_click_event_system.c"
#include "inputs/dragger_end_system.c"
#include "inputs/element_navigation_system.c"
#include "inputs/mouse_element_system.c"
#include "inputs/device_click_system.c"
#include "inputs/zevice_click_system.c"
#include "click_sound_system.c"

zox_increment_system_with_reset_extra(ClickState, zox_click_state_trigger_clicked, zox_click_state_clicked_idle, zox_click_state_trigger_released, zox_click_state_idle)
zox_increment_system_with_reset_extra(SelectState, zox_select_state_trigger_selected, zox_select_state_selected, zox_select_state_trigger_deselect, zox_select_state_deselected_idle)

void define_systems_elements_core(ecs_world_t *world) {
    // zox_define_reset_system_pip(ClickState, EcsOnLoad)
    zox_define_increment_system(ClickState, EcsOnLoad)
    zox_define_increment_system(SelectState, EcsOnLoad)
    zox_filter(raycast_query,
        [none] Element,
        [in] elements.core.CanvasPosition,
        [in] layouts2.PixelSize,
        [in] elements.core.Layer2D,
        [in] rendering.RenderDisabled,
        [none] Selectable)
    zox_system_ctx(ElementRaycastSystem, EcsOnUpdate, raycast_query,
        [in] raycasts.Raycaster,
        [in] inputs.DeviceLink,
        [out] raycasts.RaycasterTarget,
        [out] WindowRaycasted)
    // inputs
    zox_system(ZeviceClickSystem, EcsPostUpdate,
        [in] inputs.DeviceLink,
        [in] raycasts.RaycasterTarget,
        [in] WindowRaycasted,
        [out] raycasts.RaycasterResult,
        [out] ClickingEntity,
        [out] WindowTarget,
        [none] inputs.Zevice)
    zox_system(DeviceClickSystem, EcsPostUpdate,
        [in] players.PlayerLink,
        [in] raycasts.RaycasterTarget,
        [in] WindowRaycasted,
        [in] hierarchys.Children,
        [out] raycasts.RaycasterResult,
        [out] ClickingEntity,
        [out] WindowTarget,
        [none] inputs.Device)
    zox_system(ElementNavigationSystem, EcsPostUpdate,
        [in] inputs.DeviceLinks,
        [in] inputs.DeviceMode,
        [out] NavigatorState,
        [out] NavigatorTimer,
        [out] raycasts.RaycasterTarget)
    zox_system(ElementPositionSystem, EcsOnLoad,
        [in] layouts2.PixelPosition,
        [in] layouts2.PixelSize,
        [in] hierarchys.ParentLink,
        [in] elements.core.Anchor,
        [in] elements.core.CanvasLink,
        [out] transforms2.Position2D,
        [out] elements.core.CanvasPosition,
        [none] Element)
    zox_system(CanvasStackSystem, EcsOnLoad,
        [in] hierarchys.Children,
        [out] WindowToTop,
        [out] WindowsLayers,
        [out] WindowsCount,
        [none] Canvas)
    zox_system(WindowLayerSystem, EcsOnLoad,
        [in] SetWindowLayer,
        [in] elements.core.CanvasLink,
        [in] hierarchys.Children,
        [out] WindowLayer,
        [out] elements.core.Layer2D,
        [none] Window)
    zox_system(ElementSelectedSystem, EcsOnUpdate,
        [none] Element,
        [in] elements.core.SelectState,
        [out] rendering.Brightness)
    zox_system(ElementActiveSystem, EcsOnUpdate,
        [in] elements.core.ActiveState,
        [out] rendering.Brightness,
        [none] Element,
        [none] !SelectState)
    zox_system(MouseElementSystem, zox_transforms_stage,
        [in] inputs.ZeviceLink,
        [in] elements.core.Anchor,
        [in] elements.core.CanvasLink,
        [out] layouts2.PixelPosition,
        [none] MouseElement)
    zox_system(DraggerEndSystem, EcsPostLoad,
        [out] elements.core.DraggableState,
        [out] DraggerLink,
        [out] elements.core.DraggingDelta)
    zox_system(CanvasResizeSystem, EcsOnUpdate,
        [in] cameras.CameraLink,
        [in] hierarchys.Children,
        [in] cameras.ScreenToCanvas,
        [out] layouts2.PixelSize,
        [none] Canvas)
    // all ui
    zox_render2D_system(RenderTextureRenderSystem,
        [in] transforms3.TransformMatrix,
        [in] elements.core.Layer2D,
        [in] rendering.RenderDisabled,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.UvsGPULink,
        [in] rendering.core.TextureGPULink,
        [none] cameras.RenderTexture)
    zox_render2D_system(ElementRenderSystem,
        [in] transforms2.Position2D,
        [in] transforms2.Rotation2D,
        [in] transforms.Scale1D,
        [in] elements.core.Layer2D,
        [in] rendering.RenderDisabled,
        [in] rendering.Brightness,
        [in] rendering.Alpha,
        [in] rendering.core.MeshGPULink,
        [in] rendering.core.UvsGPULink,
        [in] rendering.core.TextureGPULink,
        [none] ElementRender,
        [none] !cameras.RenderTexture)
    // healthbars
    zox_system_1(ClickSoundSystem, zox_pip_mainthread,
        [in] elements.core.ClickState,
        [none] ClickMakeSound)
    if (!headless) {
        zox_system_1(ButtonClickEventSystem, zox_pip_mainthread,
            [in] ClickEvent,
            [in] elements.core.ClickState,
            [out] Clicker,
            [none] Element)
        // EcsOnLoad - zox_pip_mainthread
        zox_system_1(Element2DMeshSystem, EcsOnLoad,
            [none] Element,
            [in] layouts2.PixelSize,
            [in] rendering.MeshAlignment,
            [in] elements.core.CanvasLink,
            [out] elements.core.InitializeElement,
            [out] rendering.MeshDirty,
            [out] rendering.core.MeshVertices2D,
            [out] rendering.core.MeshGPULink,
            [out] rendering.core.TextureGPULink,
            [out] rendering.core.UvsGPULink)
    }
}