#define zox_debug_log_extract_touchscreen
// #define zox_debug_log_element_raycasting
int finger_id = 0;

void sdl_extract_touchscreen(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    if (!(event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP)) return; // sets finger position
    if (!touchscreen_entity || !ecs_is_alive(world, touchscreen_entity)) return;
    const SDL_TouchFingerEvent finger_event = event.tfinger;
    const Children *zevices = ecs_get(world, touchscreen_entity, Children);
    ecs_entity_t zevice_pointer_entity = zevices->value[0];
    const ID *id = ecs_get(world, zevice_pointer_entity, ID);
    int new_id = finger_event.fingerId + 1;
    if (event.type == SDL_FINGERDOWN) {
        if (id->value == 0) {
            finger_id = new_id;
            // zox_set(zevice_pointer_entity, ID, { new_id })
            ID *id = ecs_get_mut(world, zevice_pointer_entity, ID);
            id->value = new_id;
            ecs_modified(world, zevice_pointer_entity, ID);
            ZevicePointer *zevicePointer = ecs_get_mut(world, zevice_pointer_entity, ZevicePointer);
            devices_set_pressed_this_frame(&zevicePointer->value, 1);
            devices_set_is_pressed(&zevicePointer->value, 1);
            ecs_modified(world, zevice_pointer_entity, ZevicePointer);
            /*#ifdef zox_debug_log_extract_touchscreen
                zoxel_log(" > touchscreen pressed at [%f]\n", (float) zox_current_time);
                zoxel_log("     + touchscreen down [%ix%i]\n", zevicePointerPosition->value.x, zevicePointerPosition->value.y);
            #endif*/
        } else {
            return; // don't set pointer position
        }
    } else if (event.type == SDL_FINGERUP) {
        if (id->value == new_id) {
            finger_id = 0;
            // zox_set(zevice_pointer_entity, ID, { 0 })
            ID *id = ecs_get_mut(world, zevice_pointer_entity, ID);
            id->value = 0;
            ecs_modified(world, zevice_pointer_entity, ID);

            // try set instead
            /*unsigned char value = ecs_get(world, zevice_pointer_entity, ZevicePointer)->value;
            devices_set_released_this_frame(&value, 1);
            devices_set_is_pressed(&value, 0);
            zox_set_only(zevice_pointer_entity, ZevicePointer, { value })*/

            ZevicePointer *zevicePointer = ecs_get_mut(world, zevice_pointer_entity, ZevicePointer);
            devices_set_released_this_frame(&zevicePointer->value, 1);
            devices_set_is_pressed(&zevicePointer->value, 0);
            ecs_modified(world, zevice_pointer_entity, ZevicePointer);
            /*#ifdef zox_debug_log_extract_touchscreen
                zoxel_log(" > touchscreen released at [%f]\n", (float) zox_current_time);
            #endif*/
        } else {
            return; // don't set pointer position
        }
    } else if (event.type == SDL_FINGERMOTION) {
        if (id->value == new_id) {
            unsigned char value = ecs_get(world, zevice_pointer_entity, ZevicePointer)->value;
            if (!devices_get_is_pressed(value)) return;
            ZevicePointerDelta *zevicePointerDelta = ecs_get_mut(world, zevice_pointer_entity, ZevicePointerDelta);
            int2 motion_value = (int2) { (int) (finger_event.dx * screen_dimensions.x), (int) (- finger_event.dy * screen_dimensions.y) };
            int2_add_int2_p(&zevicePointerDelta->value, motion_value);
            ecs_modified(world, zevice_pointer_entity, ZevicePointerDelta);

            /*#ifdef zox_debug_log_extract_touchscreen
                zoxel_log(" - touchscreen moved [%ix%i]\n       - delta [%ix%i]\n", zevicePointerPosition->value.x, zevicePointerPosition->value.y, zevicePointerDelta->value.x, zevicePointerDelta->value.y);
            #endif*/
        } else {
            return; // don't set pointer position
        }
    }
    int2 finger_position = (int2) { (int) (finger_event.x * screen_dimensions.x), (int) (finger_event.y * screen_dimensions.y) };
    int2_flip_y(&finger_position, screen_dimensions);
    ZevicePointerPosition *zevicePointerPosition = ecs_get_mut(world, zevice_pointer_entity, ZevicePointerPosition);
    zevicePointerPosition->value = finger_position;
    ecs_modified(world, zevice_pointer_entity, ZevicePointerPosition);
    #ifdef zox_debug_log_extract_touchscreen
        zoxel_log(" > finger at [%ix%i]\n", finger_position.x, finger_position.y);
    #endif
}

 /*else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
    if (event.motion.which != SDL_TOUCH_MOUSEID) return; // don't trigger events if not touch input
    int2 new_position = (int2) { event.motion.x, event.motion.y };
    new_position.y = screen_dimensions.y - new_position.y;
    touchscreen->primary_touch.position = new_position;
    SDL_MouseButtonEvent *touchscreenEvent = &event.button;
    Uint8 button = touchscreenEvent->button;
    if (button == SDL_BUTTON_LEFT) {
        set_sdl_mouse_button(&touchscreen->primary_touch.value, event.type);
    }
}*/ 
// touchscreen->primary_touch.delta = int2_add(touchscreen->primary_touch.delta, );