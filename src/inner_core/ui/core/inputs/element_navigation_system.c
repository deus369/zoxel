extern void canvas_select_first_button(ecs_world_t *world, const ecs_entity_t raycaster, const ecs_entity_t canvas);

// #define zox_debug_navigation

// todo: fix this, RaycasterTarget moved to zevices
void ElementNavigationSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_iter_world()
    zox_field_in(DeviceLinks, deviceLinkss, 1)
    zox_field_in(DeviceMode, deviceModes, 2)
    zox_field_out(NavigatorState, navigatorStates, 3)
    zox_field_out(NavigatorTimer, navigatorTimers, 4)
    zox_field_out(RaycasterTarget, raycasterTargets, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(DeviceMode, deviceModes, deviceMode)
        zox_field_o(RaycasterTarget, raycasterTargets, raycasterTarget)
        zox_field_o(NavigatorState, navigatorStates, navigatorState)
        zox_field_o(NavigatorTimer, navigatorTimers, navigatorTimer)
        unsigned char device_mode = deviceMode->value;
#ifdef zox_debug_navigation
        device_mode = zox_device_mode_gamepad;
#endif
        if (device_mode != zox_device_mode_gamepad) {
            if (!navigatorState->value) {
                navigatorState->value = 1;
                navigatorTimer->value = 0;
            }
            continue;
        } else if (device_mode == zox_device_mode_gamepad && !raycasterTarget->value) {
            zox_field_e()
            const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
            canvas_select_first_button(world, e, canvas);
        }
        if (!raycasterTarget->value || !zox_alive(raycasterTarget->value)) continue;
        zox_field_i(DeviceLinks, deviceLinkss, deviceLinks)
        float2 left_stick = float2_zero;
        for (int j = 0; j < deviceLinks->length; j++) {
            const ecs_entity_t device = deviceLinks->value[j];
            if (zox_has(device, Keyboard)) {
                zox_geter(device, Keyboard, keyboard)
                if (keyboard->down.pressed_this_frame) {
                    left_stick.y -= 1;
                } else if (keyboard->up.pressed_this_frame) {
                    left_stick.y += 1;
                } else  if (keyboard->left.pressed_this_frame) {
                    left_stick.x -= 1;
                } else if (keyboard->right.pressed_this_frame) {
                    left_stick.x += 1;
                }
            } else if (zox_has(device, Gamepad)) {
                zox_geter(device, Children, zevices)
                for (int k = 0; k < zevices->length; k++) {
                    const ecs_entity_t zevice = zevices->value[k];
                    if (zox_has(zevice, ZeviceStick)) {
                        zox_geter(zevice, ZeviceDisabled, zeviceDisabled)
                        if (zeviceDisabled->value) continue;
                        zox_geter(zevice, ZeviceStick, zeviceStick)
                        left_stick.x += zeviceStick->value.x;
                        left_stick.y += zeviceStick->value.y;
                    }
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
        // using selected window, we navigation elements of that... this could be done better
        const ecs_entity_t parent = zox_get_value(raycasterTarget->value, ParentLink)
        zox_geter(parent, Children, children)
        unsigned did_find = 0;
        for (int k = 0; k < children->length; k++) {
            const ecs_entity_t child = children->value[k];
            if (zox_has(child, Selectable) && child == raycasterTarget->value) {
                did_find = 1;
                if (left_stick.y >= ui_navigation_joystick_cutoff && k > 1) {
                    raycaster_select_element(world, e, children->value[k - 1]);
                } else if (left_stick.y <= -ui_navigation_joystick_cutoff && k != children->length - 1) {
                    raycaster_select_element(world, e, children->value[k + 1]);
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
