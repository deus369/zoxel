void reset_mouse(ecs_world_t *world) {
    if (!mouse_entity || !ecs_is_alive(world, mouse_entity)) return;
    Mouse *mouse = ecs_get_mut(world, mouse_entity, Mouse);
    reset_key(&mouse->left);
    reset_key(&mouse->middle);
    reset_key(&mouse->right);
    mouse->delta = int2_zero;
    mouse->wheel = int2_zero;
    ecs_modified(world, mouse_entity, Mouse);
}

void extract_mouse(ecs_world_t *world, SDL_Event event, int2 screen_dimensions) {
    if (!mouse_entity || !ecs_is_alive(world, mouse_entity)) return;
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEWHEEL || event.type == SDL_MOUSEMOTION) {
        // SDL_Keycode key = event.key.keysym.sym;
        Mouse *mouse = ecs_get_mut(world, mouse_entity, Mouse);
        if (event.type == SDL_MOUSEMOTION) {
            if (event.motion.which == SDL_TOUCH_MOUSEID) return; // don't trigger events if touch input
            int2 new_mouse_position = (int2) { event.motion.x, event.motion.y };
            new_mouse_position.y = screen_dimensions.y - new_mouse_position.y;
            mouse->position = new_mouse_position;
            mouse->delta = int2_add(mouse->delta, (int2) { event.motion.xrel, - event.motion.yrel });
        } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            //if (event.motion.which == SDL_TOUCH_MOUSEID) return; // don't trigger events if touch input
            SDL_MouseButtonEvent* button_event = (SDL_MouseButtonEvent*)&event;
            if (button_event->which == SDL_TOUCH_MOUSEID) return; // don't trigger events if touch input
            int2 new_mouse_position = (int2) { event.motion.x, event.motion.y };
            new_mouse_position.y = screen_dimensions.y - new_mouse_position.y;
            mouse->position = new_mouse_position;
            SDL_MouseButtonEvent *mouseEvent = &event.button;
            Uint8 button = mouseEvent->button;
            if (button == SDL_BUTTON_LEFT) {
                set_mouse_button(&mouse->left, event.type);
            } else if (button == SDL_BUTTON_MIDDLE) {
                set_mouse_button(&mouse->middle, event.type);
            } else if (button == SDL_BUTTON_RIGHT) {
                set_mouse_button(&mouse->right, event.type);
            }
            // zoxel_log(" > mouse button event\n");
        } else if (event.type == SDL_MOUSEWHEEL) {
            mouse->wheel = (int2) { event.wheel.x, event.wheel.y };
        }
        ecs_modified(world, mouse_entity, Mouse);
    }
}

/*// printf("Delta: %i x %i\n", mouse->delta.x, mouse->delta.y);
//! Reverse mouse position, so bottom is 0 and top is 1.
// mouse->position.y = screen_dimensions.y - mouse->position.y;
//printf("    position: %i x %i\n", mouse->position.x, mouse->position.y);
#ifdef zoxel_on_web
//! Reverse position X in web
// mouse->position.x = screenDimensions.x - mouse->position.x;
// printf("Mouse: %ix%i\n", mouse->position.x, mouse->position.y);
#endif*/
/*if (event.type == SDL_MOUSEBUTTONDOWN)
{
    mouse->delta = (int2) { 0, 0 };
}*/
/*if (event.type == SDL_MOUSEBUTTONDOWN)
{
    mouse_begin = mouse->position;
    relative_mouse_2 = (int2) { 0, 0 };
}*/