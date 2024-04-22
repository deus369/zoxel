#ifdef zoxel_inputs
void ElementNavigationSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    zox_iter_world()
    const DeviceLinks *deviceLinks = ecs_field(it, DeviceLinks, 1);
    const DeviceMode *deviceModes = ecs_field(it, DeviceMode, 2);
    NavigatorState *navigatorStates = ecs_field(it, NavigatorState, 3);
    NavigatorTimer *navigatorTimers = ecs_field(it, NavigatorTimer, 4);
    RaycasterTarget *raycasterTargets = ecs_field(it, RaycasterTarget, 5);
    for (int i = 0; i < it->count; i++) {
        RaycasterTarget *raycasterTarget = &raycasterTargets[i];
        const DeviceMode *deviceMode = &deviceModes[i];
        NavigatorState *navigatorState = &navigatorStates[i];
        NavigatorTimer *navigatorTimer = &navigatorTimers[i];
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
        const DeviceLinks *deviceLinks2 = &deviceLinks[i];
        // zoxel_log(" > raycasterTarget->value %lu\n", raycasterTarget->value);
        for (int j = 0; j < deviceLinks2->length; j++) {
            const ecs_entity_t device_entity = deviceLinks2->value[j];
            if (!zox_has(device_entity, Gamepad)) continue;
            const Children *zevices = ecs_get(world, device_entity, Children);
            for (int k = 0; k < zevices->length; k++) {
                ecs_entity_t zevice_entity = zevices->value[k];
                if (zox_has(zevice_entity, ZeviceStick)) {
                    const ZeviceDisabled *zeviceDisabled = ecs_get(world, zevice_entity, ZeviceDisabled);
                    if (zeviceDisabled->value) continue;
                    const ZeviceStick *zeviceStick = ecs_get(world, zevice_entity, ZeviceStick);
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
        ecs_entity_t parent_entity = ecs_get(world, raycasterTarget->value, ParentLink)->value;
        const Children *children = ecs_get(world, parent_entity, Children);
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
