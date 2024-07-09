// #define zox_debug_zevice_states
/*#ifdef zox_mod_ui
extern void raycaster_select_element(ecs_world_t *world, const ecs_entity_t raycaster_entity, const ecs_entity_t element);
#endif*/

// this disables any buttons (zevices) of a device, until they are released, then they get auto re enabled
void disable_inputs_until_release(ecs_world_t *world, const ecs_entity_t player, const unsigned char new_device_mode) {
    if (!player) return;
    if (new_device_mode != zox_device_mode_gamepad) {
/*#ifdef zox_mod_ui
        raycaster_select_element(world, player, 0);
#endif*/
    }
    const DeviceLinks *deviceLinks = zox_get(player, DeviceLinks)
    for (int j = 0; j < deviceLinks->length; j++) {
        ecs_entity_t device_entity = deviceLinks->value[j];
        if (zox_has(device_entity, Gamepad)) {
            const Children *zevices = zox_get(device_entity, Children)
            for (int k = 0; k < zevices->length; k++) {
                ecs_entity_t zevice_entity = zevices->value[k];
                ZeviceDisabled *zeviceDisabled = zox_get_mut(zevice_entity, ZeviceDisabled)
                if (!zeviceDisabled->value) {
                    unsigned char has_input = 0;
                    if (zox_has(zevice_entity, ZeviceStick)) {
                        const ZeviceStick *zeviceStick = zox_get(zevice_entity, ZeviceStick)
                        has_input = zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
                    } else if (zox_has(zevice_entity, ZeviceButton)) {
                        const ZeviceButton *zeviceButton = zox_get(zevice_entity, ZeviceButton)
                        has_input = zeviceButton->value !=  0;
                    }
                    if (has_input) {
                        zeviceDisabled->value = 1;
                        zox_modified(zevice_entity, ZeviceDisabled);
#ifdef zox_debug_zevice_states
                        zox_log("  = button disabled [%lu] at %f\n", zevice_entity, zox_current_time)
#endif
                    }
                }
            }
        }
    }
}
