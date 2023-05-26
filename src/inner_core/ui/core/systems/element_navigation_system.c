#ifdef zoxel_inputs
    #define ui_navigation_joystick_cutoff 0.6f
    #define ui_navigation_timing 0.3
    #define restore_joystick_cutoff 0.06f

    void ElementNavigationSystem(ecs_iter_t *it) {
        double delta_time = zox_delta_time;
        ecs_world_t *world = it->world;
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
                if (navigatorState->value == 0) {
                    // zoxel_log("   > gamepad state disabled [%i]\n", navigatorState->value);
                    navigatorState->value = 1;
                    navigatorTimer->value = 0;
                }
                continue;
            }
            const DeviceLinks *deviceLinks2 = &deviceLinks[i];
            // zoxel_log(" > raycasterTarget->value %lu\n", raycasterTarget->value);
            for (int j = 0; j < deviceLinks2->length; j++) {
                ecs_entity_t device_entity = deviceLinks2->value[j];
                if (ecs_has(world, device_entity, Gamepad)) {
                    const Gamepad *gamepad = ecs_get(world, device_entity, Gamepad);
                    if (float_abs(gamepad->left_stick.value.y) < restore_joystick_cutoff) {
                        // if (navigatorState->value == 1) zoxel_log("     > reset gamepad left stick\n");
                        navigatorState->value = 0;
                    }
                    // if stops input
                    if (navigatorState->value != 0) {
                        // here we are waiting for gamepad to stop moving, as didn't start within gamepad mode
                        break;
                    } else if (float_abs(gamepad->left_stick.value.y) < ui_navigation_joystick_cutoff) {
                        navigatorTimer->value = 0;
                        break;
                    } else if (navigatorTimer->value > 0) {
                        navigatorTimer->value -= delta_time;
                        if (navigatorTimer->value < 0) navigatorTimer->value = 0;
                        break;
                    }
                    if (raycasterTarget->value == 0 || !ecs_is_alive(world, raycasterTarget->value)) break;
                    //zoxel_log(" > left_stick.value.y: %f\n", gamepad->left_stick.value.y);
                    ecs_entity_t parent_entity = ecs_get(world, raycasterTarget->value, ParentLink)->value;
                    const Children *children = ecs_get(world, parent_entity, Children);
                    unsigned did_find = 0;
                    for (int k = 0; k < children->length; k++) {
                        ecs_entity_t child_entity = children->value[k];
                        if (ecs_has(world, child_entity, Selectable) && child_entity == raycasterTarget->value) {
                            // zoxel_log(" > found selectable [%i] out of [%i] - %lu\n", k, children->length, child_entity);
                            did_find = 1;
                            if (gamepad->left_stick.value.y >= ui_navigation_joystick_cutoff && k > 1) {
                                // zoxel_log("     > moved up ui to [%i] - %lu\n", (k - 1), children->value[k - 1]);
                                raycaster_select_ui(world, raycasterTarget, children->value[k - 1]);
                                // set_ui_selected_mut(world, raycasterTarget->value);
                                set_selectable_state_mut(world, raycasterTarget->value, 1);
                            } else if (gamepad->left_stick.value.y <= -ui_navigation_joystick_cutoff && k != children->length - 1) {
                                // zoxel_log("     > moved down ui to [%i] - %lu\n", (k + 1), children->value[k + 1]);
                                raycaster_select_ui(world, raycasterTarget, children->value[k + 1]);
                                // set_ui_selected_mut(world, raycasterTarget->value);
                                set_selectable_state_mut(world, raycasterTarget->value, 1);
                            }
                            break;
                        }
                    }
                    if (did_find) {
                        navigatorTimer->value += ui_navigation_timing;
                    }
                    break;
                    /*if (!did_find) {
                        zoxel_log(" ! selectable not found out of [%i]\n", children->length);
                    }*/
                    // select left and right later
                }
            }
        }
    }
    zox_declare_system(ElementNavigationSystem)
#endif