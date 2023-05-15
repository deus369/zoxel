#define zox_debug_log_extract_touchscreen
#define zox_debug_log_element_raycasting

void extract_touchscreen(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    if (!touchscreen_entity || !ecs_is_alive(world, touchscreen_entity)) return;
    if (event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP) {
        Touchscreen *touchscreen = ecs_get_mut(world, touchscreen_entity, Touchscreen);
        if (event.type == SDL_FINGERMOTION) {
            int2_add_int2_p(&touchscreen->primary_touch.delta, (int2) {
                (int) (event.tfinger.dx * screen_dimensions.x), (int) (- event.tfinger.dy * screen_dimensions.y) });
            int2 new_position = (int2) {
                (int) (event.tfinger.x * screen_dimensions.x), (int) (event.tfinger.y * screen_dimensions.y) };
            int2_flip_y(&new_position, screen_dimensions);
            touchscreen->primary_touch.position = new_position;
            #ifdef zox_debug_log_extract_touchscreen
                zoxel_log(" - touchscreen moved [%ix%i]\n       - delta [%ix%i]\n",
                    touchscreen->primary_touch.position.x, touchscreen->primary_touch.position.y,
                    touchscreen->primary_touch.delta.x, touchscreen->primary_touch.delta.y);
            #endif
        } else if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP) {
            touchscreen->primary_touch.value.pressed_this_frame = event.type == SDL_FINGERDOWN;
            touchscreen->primary_touch.value.released_this_frame = event.type == SDL_FINGERUP;
            if (touchscreen->primary_touch.value.pressed_this_frame) {
                touchscreen->primary_touch.value.is_pressed = 1;
                int2 new_position = (int2) { (int) (event.tfinger.x * screen_dimensions.x),
                    (int) (event.tfinger.y * screen_dimensions.y) };
                int2_flip_y(&new_position, screen_dimensions);
                touchscreen->primary_touch.position = new_position;
                #ifdef zox_debug_log_extract_touchscreen
                    zoxel_log(" > touchscreen pressed at [%f]\n", (float) zox_current_time);
                #endif
            } else if (touchscreen->primary_touch.value.released_this_frame) {
                touchscreen->primary_touch.value.is_pressed = 0;
                #ifdef zox_debug_log_extract_touchscreen
                    zoxel_log(" > touchscreen released at [%f]\n", (float) zox_current_time);
                #endif
            }
            #ifdef zox_debug_log_extract_touchscreen
                zoxel_log("     + touchscreen down [%ix%i]\n", touchscreen->primary_touch.position.x, touchscreen->primary_touch.position.y);
            #endif
        }
        ecs_modified(world, touchscreen_entity, Touchscreen);
    }
}

void device_reset_touchscreen(ecs_world_t *world, ecs_entity_t e) {
    if (!touchscreen_entity || !ecs_is_alive(world, e)) return;
    Touchscreen *touchscreen = ecs_get_mut(world, e, Touchscreen);
    reset_key(&touchscreen->primary_touch.value);
    touchscreen->primary_touch.delta = int2_zero;
    ecs_modified(world, e, Touchscreen);
}

 /*else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
    if (event.motion.which != SDL_TOUCH_MOUSEID) return; // don't trigger events if not touch input
    int2 new_position = (int2) { event.motion.x, event.motion.y };
    new_position.y = screen_dimensions.y - new_position.y;
    touchscreen->primary_touch.position = new_position;
    SDL_MouseButtonEvent *touchscreenEvent = &event.button;
    Uint8 button = touchscreenEvent->button;
    if (button == SDL_BUTTON_LEFT) {
        set_mouse_button(&touchscreen->primary_touch.value, event.type);
    }
}*/ 
// touchscreen->primary_touch.delta = int2_add(touchscreen->primary_touch.delta, );