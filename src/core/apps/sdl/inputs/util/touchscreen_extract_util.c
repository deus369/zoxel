// #define zox_debug_log_extract_touchscreen
// #define zox_debug_log_element_raycasting
//int finger_id = 0;
int touch_devices_count = 0;
int touch_fingers_count = 0;

void set_id(ecs_world_t *world, ecs_entity_t e, int new_id) {
    ID *id = zox_get_mut(e, ID)
    if (id->value != new_id) {
        id->value = new_id;
        zox_modified(e, ID)
        //finger_id = new_id;
    }
}

void finger_released(ecs_world_t *world, ecs_entity_t e) {
    ZevicePointer *zevicePointer = zox_get_mut(e, ZevicePointer)
    // this shouldn't happen... but on Steam Deck it does
    if (devices_get_is_pressed(zevicePointer->value)) {
        // zox_logg("finger released!\n")
        devices_set_released_this_frame(&zevicePointer->value, 1);
        devices_set_is_pressed(&zevicePointer->value, 0);
        zox_modified(e, ZevicePointer)
        set_id(world, e, 0);
    }
}

void sdl_extract_touchscreen(ecs_world_t *world, const Children *zevices, const int2 touchscreen_size) {
    touch_devices_count = SDL_GetNumTouchDevices();
    // if (!touch_devices_count) return;
    // get touchscreen finger one
    ecs_entity_t zevice_pointer_entity = zevices->value[0];
    const ID *id = zox_get(zevice_pointer_entity, ID)
    // zox_log("   > fingers_count [%i]\n", fingers_count)
    unsigned char found_finger = 0;
    touch_fingers_count = 0;
    for (int j = 0; j < touch_devices_count; j++) {
        SDL_TouchID touchscreen_id = SDL_GetTouchDevice(j);
        int fingers_count = SDL_GetNumTouchFingers(touchscreen_id);
        touch_fingers_count += fingers_count;
        for (int i = 0; i < fingers_count; i++) {
            SDL_Finger *finger = SDL_GetTouchFinger(touchscreen_id, i);
            int new_id = 0; // finger_event.fingerId + 1;
            if (!finger) {
                zox_log("   finger [%i] is null\n", i)
                continue;
            }
            new_id = finger->id + 1;
            if (id->value && id->value != new_id) continue; // if not right finger, don't set position
            int2 finger_position = (int2) { (int) (finger->x * touchscreen_size.x), (int) (finger->y * touchscreen_size.y) };
            int2_flip_y(&finger_position, touchscreen_size);
            ZevicePointerPosition *zevicePointerPosition = zox_get_mut(zevice_pointer_entity, ZevicePointerPosition);
            // zox_log("   finger [%i]: %fx%f > %f\n", finger->id, finger->x, finger->y, finger->pressure)
            if (!id->value) { // first touch
                set_id(world, zevice_pointer_entity, new_id);
                ZevicePointer *zevicePointer = zox_get_mut(zevice_pointer_entity, ZevicePointer)
                devices_set_pressed_this_frame(&zevicePointer->value, 1);
                devices_set_is_pressed(&zevicePointer->value, 1);
                zox_modified(zevice_pointer_entity, ZevicePointer)
            } else if (id->value == new_id) {   // second or more touch
                int2 delta_finger = finger_position;
                int2_sub_int2(&delta_finger, zevicePointerPosition->value);
                ZevicePointerDelta *zevicePointerDelta = zox_get_mut(zevice_pointer_entity, ZevicePointerDelta)
                zevicePointerDelta->value = delta_finger;
                zox_modified(zevice_pointer_entity, ZevicePointerDelta)
            }
            zevicePointerPosition->value = finger_position;
            zox_modified(zevice_pointer_entity, ZevicePointerPosition)
            #ifdef zox_debug_log_extract_touchscreen
                zox_log(" > finger at [%ix%i]\n", finger_position.x, finger_position.y)
            #endif
            found_finger = 1;
        }
        if (found_finger) break;
    }
    if (!found_finger) finger_released(world, zevice_pointer_entity);
    // if (!fingers_count) finger_released(world, zevice_pointer_entity);
}
