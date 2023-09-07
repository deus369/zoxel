#define zox_debug_log_extract_touchscreen
// #define zox_debug_log_element_raycasting

void sdl_extract_touchscreen(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    if (event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP) { // sets finger position
        if (!touchscreen_entity || !ecs_is_alive(world, touchscreen_entity)) return;
        const Children *zevices = ecs_get(world, touchscreen_entity, Children);
        ecs_entity_t zevice_pointer_entity = zevices->value[0];
        ZevicePointerPosition *zevicePointerPosition = ecs_get_mut(world, zevice_pointer_entity, ZevicePointerPosition);
        int2 new_position = (int2) { (int) (event.tfinger.x * screen_dimensions.x), (int) (event.tfinger.y * screen_dimensions.y) };
        int2_flip_y(&new_position, screen_dimensions);
        zevicePointerPosition->value = new_position;
        ecs_modified(world, zevice_pointer_entity, ZevicePointerPosition);
        if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP) {
            ZevicePointer *zevicePointer = ecs_get_mut(world, zevice_pointer_entity, ZevicePointer);
            if (event.type == SDL_FINGERDOWN) {
                devices_set_pressed_this_frame(&zevicePointer->value, 1);
                devices_set_is_pressed(&zevicePointer->value, 1);
                #ifdef zox_debug_log_extract_touchscreen
                    zoxel_log(" > touchscreen pressed at [%f]\n", (float) zox_current_time);
                #endif
            } else {
                devices_set_released_this_frame(&zevicePointer->value, 1);
                devices_set_is_pressed(&zevicePointer->value, 0);
                #ifdef zox_debug_log_extract_touchscreen
                    zoxel_log(" > touchscreen released at [%f]\n", (float) zox_current_time);
                #endif
            }
            ecs_modified(world, zevice_pointer_entity, ZevicePointer);
            #ifdef zox_debug_log_extract_touchscreen
                zoxel_log("     + touchscreen down [%ix%i]\n", zevicePointerPosition->value.x, zevicePointerPosition->value.y);
            #endif
        } else { // if (event.type == SDL_FINGERMOTION) {
            ZevicePointerDelta *zevicePointerDelta = ecs_get_mut(world, zevice_pointer_entity, ZevicePointerDelta);
            int2 motion_value = (int2) { (int) (event.tfinger.dx * screen_dimensions.x), (int) (- event.tfinger.dy * screen_dimensions.y) };
            int2_add_int2_p(&zevicePointerDelta->value, motion_value);
            ecs_modified(world, zevice_pointer_entity, ZevicePointerDelta);
            #ifdef zox_debug_log_extract_touchscreen
                zoxel_log(" - touchscreen moved [%ix%i]\n       - delta [%ix%i]\n", zevicePointerPosition->value.x, zevicePointerPosition->value.y, zevicePointerDelta->value.x, zevicePointerDelta->value.y);
            #endif
        }
    }
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