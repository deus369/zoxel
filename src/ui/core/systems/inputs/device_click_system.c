// todo: reuse parts of ZeviceClickSystem in this
// this is now from zevice
void DeviceClickSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(PlayerLink, playerLinks, 1)
    zox_field_in(Children, childrens, 4)
    zox_field_in(RaycasterTarget, raycasterTargets, 2)
    // zox_field_out(RaycasterResult, raycasterResults, 5)
    zox_field_in(WindowRaycasted, windowRaycasteds, 3)
    zox_field_out(WindowTarget, windowTargets, 7)
    zox_field_out(ClickingEntity, clickingEntitys, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(PlayerLink, playerLinks, playerLink)
        const ecs_entity_t player = playerLink->value;
        if (!player) continue;
        if (!player || !zox_has(player, CanvasLink)) continue;
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        if (!canvas) continue;
        zox_field_i(Children, childrens, children)
        byte click_type = 0;
        for (int j = 0; j < children->length; j++) {
            const ecs_entity_t zevice = children->value[j];
            if (!zevice) continue;
            if (!zox_has(zevice, ZeviceButton)) continue;
            if (!zox_has(zevice, DeviceButtonType)) continue;
            const byte button_type = zox_get_value(zevice, DeviceButtonType)
            if (button_type == zox_device_button_a) {
                const byte disabled = zox_get_value(zevice, ZeviceDisabled)
                if (!disabled) {
                    const byte click_value = zox_get_value(zevice, ZeviceButton)
                    if (devices_get_pressed_this_frame(click_value)) click_type = 1;
                    else if (devices_get_released_this_frame(click_value)) click_type = 2;
                }
            }
        }
        if (click_type == 0) continue;
        const byte device_mode = zox_get_value(player, DeviceMode)
        // zox_field_e()
        zox_field_i(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i(WindowRaycasted, windowRaycasteds, windowRaycasted)
        // zox_field_o(RaycasterResult, raycasterResults, raycasterResult)
        zox_field_o(ClickingEntity, clickingEntitys, clickingEntity)
        zox_field_o(WindowTarget, windowTargets, windowTarget)
        // used for virtual joysticks to see if a t arget was raycasted, todo: move to raycast system
        // raycasterResult->value = raycasterTarget->value || windowRaycasted->value;
        // released
        if (click_type == 1) {
            clickingEntity->value = raycasterTarget->value; // clicked
            on_element_clicked(world, player, clickingEntity->value);
        }
        if (click_type == 1) { // clicked
            if (windowRaycasted->value != windowTarget->value) {
                windowTarget->value = windowRaycasted->value;
                // zox_log(" > player window target [%lu]\n", windowTarget->value)
                // todo: set it's window to top
                // now set WindowToTop entity to windowTarget->value
                // then next in canvas system, reset windows layers to top of window stack
                zox_set(canvas, WindowToTop, { windowTarget->value })
            }
            if (zox_has(raycasterTarget->value, Dragable)) {
                byte drag_mode = zox_drag_mode_none;
                if (device_mode == zox_device_mode_keyboardmouse) drag_mode = zox_drag_mode_mouse;
                else if (device_mode == zox_device_mode_touchscreen) drag_mode = zox_drag_mode_finger;
                set_element_dragged(world, player, raycasterTarget->value, drag_mode);
            }
        } else if (click_type == 2) { // released
            if (raycasterTarget->value == clickingEntity->value) on_element_released(world, player, raycasterTarget->value);
            clickingEntity->value = 0;
        }
    }
} zox_declare_system(DeviceClickSystem)
