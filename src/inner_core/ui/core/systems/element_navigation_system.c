#ifdef zoxel_inputs
void ElementNavigationSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(NavigatorState, navigatorStates, 3)
    zox_field_out(NavigatorTimer, navigatorTimers, 4)
    zox_field_out(RaycasterTarget, raycasterTargets, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(DeviceMode, deviceModes, deviceMode)
        zox_field_i_out(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_i_out(NavigatorState, navigatorStates, navigatorState)
        zox_field_i_out(NavigatorTimer, navigatorTimers, navigatorTimer)
        if (deviceMode->value != zox_device_mode_gamepad) {
            if (!navigatorState->value) {
                // zoxel_log("   > gamepad state disabled [%i]\n", navigatorState->value);
                navigatorState->value = 1;
                navigatorTimer->value = 0;
            }
            continue;
        }
        if (!raycasterTarget->value) zox_logg(" > raycaster not selected\n")
        if (!raycasterTarget->value || !ecs_is_alive(world, raycasterTarget->value)) continue;
        float2 left_stick = float2_zero;
        zox_field_i_in(DeviceLinks, deviceLinkss, deviceLinks)
        // zoxel_log(" > raycasterTarget->value %lu\n", raycasterTarget->value);
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device_entity = deviceLinks->value[j];
            if (!zox_has(device_entity, Gamepad)) continue;
            const Children *zevices = zox_get(device_entity, Children)
            for (int k = 0; k < zevices->length; k++) {
                ecs_entity_t zevice_entity = zevices->value[k];
                if (zox_has(zevice_entity, ZeviceStick)) {
                    const ZeviceDisabled *zeviceDisabled = zox_get(zevice_entity, ZeviceDisabled)
                    if (zeviceDisabled->value) continue;
                    const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick);
                    left_stick = zeviceStick->value;
                    break;
                }
            }

        }
        // here cut
        if (float_abs(left_stick.y) < restore_joystick_cutoff) {
            navigatorState->value = 0;
            continue;
        }
        // if stops input
        if (navigatorState->value == 1) {
            // here we are waiting for gamepad to stop moving, as didn't start within gamepad mode
            continue;
        } else if (float_abs(left_stick.y) < ui_navigation_joystick_cutoff) {
            navigatorTimer->value = 0;
            continue;
        } else if (navigatorTimer->value > 0) {
            navigatorTimer->value -= delta_time;
            if (navigatorTimer->value < 0) navigatorTimer->value = 0;
            continue;
        }
        const ecs_entity_t parent_entity = zox_get_value(raycasterTarget->value, ParentLink)
        const Children *children = zox_get(parent_entity, Children);
        unsigned did_find = 0;
        for (int k = 0; k < children->length; k++) {
            ecs_entity_t child_entity = children->value[k];
            if (zox_has(child_entity, Selectable) && child_entity == raycasterTarget->value) {
                did_find = 1;
                if (left_stick.y >= ui_navigation_joystick_cutoff && k > 1) {
                    raycaster_select_ui(world, raycasterTarget, children->value[k - 1]);
                    set_selectable_state_mut(world, raycasterTarget->value, 1);
                } else if (left_stick.y <= -ui_navigation_joystick_cutoff && k != children->length - 1) {
                    raycaster_select_ui(world, raycasterTarget, children->value[k + 1]);
                    set_selectable_state_mut(world, raycasterTarget->value, 1);
                }
                break;
            }
        }
        if (did_find) {
            if (navigatorTimer->value < -ui_navigation_timing / 2) navigatorTimer->value = ui_navigation_timing;
            else navigatorTimer->value += ui_navigation_timing;
        }
    }
} zox_declare_system(ElementNavigationSystem)
#endif
