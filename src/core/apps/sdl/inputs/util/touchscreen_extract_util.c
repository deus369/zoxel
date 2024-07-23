// #define zox_log_fingers
// #define zox_debug_log_element_raycasting
int touch_devices_count = 0;
int touch_fingers_count = 0;
// todo: debug label for fingers

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
    }
}

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
                const int2 delta_finger = int2_sub_int2_(finger_position, zevicePointerPosition->value);
                zevicePointerDelta->value = delta_finger;
                zevicePointerPosition->value = finger_position;
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
                int finger_id = finger->id + 1; // finger_event.fingerId + 1;
                set_id(world, zevice, finger_id);
                zox_get_muter(zevice, ZevicePointer, zevicePointer)
                zox_get_muter(zevice, ZevicePointerPosition, zevicePointerPosition)
                devices_set_pressed_this_frame(&zevicePointer->value, 1);
                devices_set_is_pressed(&zevicePointer->value, 1);
                int2 finger_position = (int2) { (int) (finger->x * touchscreen_size.x), (int) (finger->y * touchscreen_size.y) };
                int2_flip_y(&finger_position, touchscreen_size);
                zevicePointerPosition->value = finger_position;
#ifdef zox_log_fingers
                zox_log(" + finger touched [%lu] fingerid [%i]\n", zevice, finger_id)
#endif
            }
        }
    }
}

    /*touch_fingers_count = 0;
    touch_devices_count = SDL_GetNumTouchDevices();
    if (touch_devices_count == 0) return;
    SDL_TouchID touchscreen_id = SDL_GetTouchDevice(0);
    const int fingers_count = SDL_GetNumTouchFingers(touchscreen_id);
    touch_fingers_count += fingers_count;

        // zox_log("   > fingers_count [%i]\n", fingers_count)
        unsigned char found_finger = 0;
        for (int j = 0; j < fingers_count; j++) {
            SDL_Finger *finger = SDL_GetTouchFinger(touchscreen_id, j);
            if (!finger) {
                zox_log("   finger [%i] is null\n", j)
                continue;
            }*/

        /*unsigned char found_finger = 0;
        for (int j = 0; j < touch_devices_count; j++) {
            SDL_TouchID touchscreen_id = SDL_GetTouchDevice(j);
            int fingers_count = SDL_GetNumTouchFingers(touchscreen_id);
            touch_fingers_count += fingers_count;
            for (int k = 0; k < fingers_count; k++) {
                SDL_Finger *finger = SDL_GetTouchFinger(touchscreen_id, k);
                int new_id = finger->id + 1; // finger_event.fingerId + 1;
                // if id is not this finger and already exists, continue
                if (zevice_id && zevice_id != new_id) continue;
                // otherwise we found it! used to release finger when no sdl data found
                // quick hack atm for first fingers
                if (new_id == first_finger_found) continue;
                first_finger_found = new_id;
                found_finger = 1;
                // zox_log("   finger [%i]: %fx%f > %f\n", finger->id, finger->x, finger->y, finger->pressure)
                zox_get_muter(zevice, ZevicePointerPosition, zevicePointerPosition)
                if (!zevice_id) { // first touch
                } else if (zevice_id == new_id) {   // second or more touch
                }
                zevicePointerPosition->value = finger_position;
#ifdef zox_debug_log_extract_touchscreen
                zox_log(" > finger at [%ix%i]\n", finger_position.x, finger_position.y)
#endif
                j = touch_devices_count; // skip to next zevice
                break; // since we applied finger to this zevice, go to next zevice
            }
        }
        if (zevice_id && !found_finger) {
        }*/
