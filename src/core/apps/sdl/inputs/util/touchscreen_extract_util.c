// #define zox_log_fingers
// #define zox_debug_log_element_raycasting
int touch_devices_count = 0;
int touch_fingers_count = 0;

unsigned char touchscreen_has_id(ecs_world_t *world, const Children *zevices, const int id) {
    for (int i = 0; i < zevices->length; i++) {
        const ecs_entity_t zevice = zevices->value[i];
        if (!zox_has(zevice, Finger)) continue;
        if (id == zox_gett_value(zevice, ID)) return 1;
    }
    return 0;
}

SDL_Finger* find_finger_unused(ecs_world_t *world, const Children *zevices) {
    for (int i = 0; i < touch_devices_count; i++) {
        SDL_TouchID touchscreen_id = SDL_GetTouchDevice(i);
        int fingers_count = SDL_GetNumTouchFingers(touchscreen_id);
        touch_fingers_count += fingers_count;
        for (int k = 0; k < fingers_count; k++) {
            SDL_Finger *finger = SDL_GetTouchFinger(touchscreen_id, k);
            int new_id = finger->id + 1;
            if (!touchscreen_has_id(world, zevices, new_id)) return finger;
        }
    }
    return NULL;
}

SDL_Finger* find_finger(int finger_id) {
    for (int j = 0; j < touch_devices_count; j++) {
        SDL_TouchID touchscreen_id = SDL_GetTouchDevice(j);
        int fingers_count = SDL_GetNumTouchFingers(touchscreen_id);
        touch_fingers_count += fingers_count;
        for (int k = 0; k < fingers_count; k++) {
            SDL_Finger *finger = SDL_GetTouchFinger(touchscreen_id, k);
            if (finger_id == (finger->id + 1)) return finger;
        }
    }
    return NULL;
}

void set_id(ecs_world_t *world, const ecs_entity_t e, const int new_id) {
    if (!zox_has(e, ID)) {
        zox_log(" ! invalid zevice, no ID\n")
        return;
    }
    zox_get_muter(e, ID, id)
    id->value = new_id;
}

void finger_released(ecs_world_t *world, const ecs_entity_t e) {
    zox_get_muter(e, ZevicePointer, zevicePointer)
    if (devices_get_is_pressed(zevicePointer->value)) {
        devices_set_is_pressed(&zevicePointer->value, 0);
        devices_set_released_this_frame(&zevicePointer->value, 1);
        set_id(world, e, 0);
        global_any_fingers_down = 1; // one more frame
        // zox_get_muter(e, ZevicePointerPosition, zevicePointerPosition)
        // zox_get_muter(e, ZevicePointerDelta, zevicePointerDelta)
        // zevicePointerPosition->value = int2_hidden;
        // zevicePointerDelta->value = int2_zero;
        // todo: this is still used for buttons due to click releasing, need to reset this on frame after
    }
}

void sdl_extract_touchscreen(ecs_world_t *world, const Children *zevices, const int2 touchscreen_size) {
    touch_fingers_count = 0;
    touch_devices_count = SDL_GetNumTouchDevices();
    for (int i = 0; i < zevices->length; i++) {
        const ecs_entity_t zevice = zevices->value[i];
        if (!zox_has(zevice, Finger)) continue;
        const int zevice_id = zox_get_value(zevice, ID)
        if (zevice_id) {
            SDL_Finger *finger = find_finger(zevice_id);
            if (finger) {
                zox_get_muter(zevice, ZevicePointerPosition, zevicePointerPosition)
                zox_get_muter(zevice, ZevicePointerDelta, zevicePointerDelta)
                int2 finger_position = (int2) { (int) (finger->x * touchscreen_size.x), (int) (finger->y * touchscreen_size.y) };
                int2_flip_y(&finger_position, touchscreen_size);
                if (!int2_equals(zevicePointerPosition->value, int2_hidden)) {
                    const int2 delta_finger = int2_sub_int2_(finger_position, zevicePointerPosition->value);
                    zevicePointerDelta->value = delta_finger;
                }
                zevicePointerPosition->value = finger_position;
                global_any_fingers_down = 1;
#ifdef zox_log_fingers
                zox_log(" > finger touching [%lu] fingerid [%i]\n", zevice, zevice_id)
#endif
            } else {
                finger_released(world, zevice);
#ifdef zox_log_fingers
                zox_log(" - finger released [%lu] fingerid [%i]\n", zevice, zevice_id)
#endif
            }
        } else {
            // get unused finger! find a finger that isn't used yet
            SDL_Finger *finger = find_finger_unused(world, zevices);
            if (finger) {
                const int finger_id = finger->id + 1;
                // zox_log(" + touch down: %i\n", finger_id)
                set_id(world, zevice, finger_id);
                zox_get_muter(zevice, ZevicePointer, zevicePointer)
                zox_get_muter(zevice, ZevicePointerPosition, zevicePointerPosition)
                devices_set_pressed_this_frame(&zevicePointer->value, 1);
                devices_set_is_pressed(&zevicePointer->value, 1);
                int2 finger_position = (int2) { (int) (finger->x * touchscreen_size.x), (int) (finger->y * touchscreen_size.y) };
                int2_flip_y(&finger_position, touchscreen_size);
                zevicePointerPosition->value = finger_position;
                global_any_fingers_down = 1;
#ifdef zox_log_fingers
                zox_log(" + finger touched [%lu] fingerid [%i]\n", zevice, finger_id)
#endif
            }
        }
    }
}
