// #define zox_debug_log_extract_mouse

void sdl_extract_mouse(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    if (!mouse_entity || !ecs_is_alive(world, mouse_entity)) return;
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL || event.type == SDL_MOUSEMOTION) {
        Mouse *mouse = ecs_get_mut(world, mouse_entity, Mouse);
        if (event.type == SDL_MOUSEMOTION) {
            // don't trigger events if touch input
            if (event.motion.which == SDL_TOUCH_MOUSEID) return;
            int2 new_position = (int2) { event.motion.x, event.motion.y };
            int2_flip_y(&new_position, screen_dimensions);
            mouse->position = new_position;
            mouse->delta = int2_add(mouse->delta, (int2) { event.motion.xrel, - event.motion.yrel });
            #ifdef zox_debug_log_extract_mouse
                zoxel_log(" - mouse moved [%ix%i]\n     - delta [%ix%i]\n", mouse->position.x, mouse->position.y, mouse->delta.x, mouse->delta.y);
            #endif
        } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            // don't trigger events if touch input
            SDL_MouseButtonEvent* button_event = (SDL_MouseButtonEvent*) &event;
            if (button_event->which == SDL_TOUCH_MOUSEID) return;
            SDL_MouseButtonEvent *mouseEvent = &event.button;
            Uint8 button = mouseEvent->button;
            if (button == SDL_BUTTON_LEFT) set_sdl_mouse_button(&mouse->left, event.type);
            else if (button == SDL_BUTTON_MIDDLE) set_sdl_mouse_button(&mouse->middle, event.type);
            else if (button == SDL_BUTTON_RIGHT) set_sdl_mouse_button(&mouse->right, event.type);
            int2 new_position = (int2) { event.motion.x, event.motion.y };
            int2_flip_y(&new_position, screen_dimensions);
            mouse->position = new_position;
            #ifdef zox_debug_log_extract_mouse
                zoxel_log(" > mouse down [%ix%i]\n", mouse->position.x, mouse->position.y);
            #endif
        } else if (event.type == SDL_MOUSEWHEEL) {
            mouse->wheel = (int2) { event.wheel.x, event.wheel.y };
        }
        ecs_modified(world, mouse_entity, Mouse);
    }
}