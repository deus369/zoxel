void reset_mouse(ecs_world_t *world) {
    if (!mouse_entity || !ecs_is_alive(world, mouse_entity)) {
        return;
    }
    Mouse *mouse = ecs_get_mut(world, mouse_entity, Mouse);
    reset_key(&mouse->left);
    reset_key(&mouse->middle);
    reset_key(&mouse->right);
    mouse->wheel = (int2) { 0, 0 };
    mouse->delta = (int2) { 0, 0 };
    ecs_modified(world, mouse_entity, Mouse);
}

void SetMouseKey(PhysicalButton *key, int eventType) {
    unsigned char keyDown = eventType == SDL_MOUSEBUTTONDOWN;
    unsigned char keyReleased = eventType == SDL_MOUSEBUTTONUP;
    key->pressed_this_frame = keyDown;
    key->released_this_frame = keyReleased;
    if (keyDown) {
        key->is_pressed = 1;
    } else if (keyReleased) {
        key->is_pressed = 0;
    }
}

void extract_mouse(ecs_world_t *world, SDL_Event event) {
    if (!mouse_entity || !ecs_is_alive(world, mouse_entity)) {
        return;
    }
    int eventType = event.type;
    if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP || eventType == SDL_MOUSEWHEEL || eventType == SDL_MOUSEMOTION) {
        // SDL_Keycode key = event.key.keysym.sym;
        Mouse *mouse = ecs_get_mut(world, mouse_entity, Mouse);
        if (eventType == SDL_MOUSEMOTION) {
            int2 new_mouse_position = (int2) { event.motion.x, event.motion.y };
            new_mouse_position.y = screen_dimensions.y - new_mouse_position.y;
            mouse->position = new_mouse_position;
            mouse->delta = int2_add(mouse->delta, (int2) { event.motion.xrel, - event.motion.yrel });
            // printf("Delta: %i x %i\n", mouse->delta.x, mouse->delta.y);
            //! Reverse mouse position, so bottom is 0 and top is 1.
            // mouse->position.y = screen_dimensions.y - mouse->position.y;
            //printf("    position: %i x %i\n", mouse->position.x, mouse->position.y);
#ifdef WEB_BUILD
            //! Reverse position X in web
            // mouse->position.x = screenDimensions.x - mouse->position.x;
            // printf("Mouse: %ix%i\n", mouse->position.x, mouse->position.y);
#endif
        } else if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP) {
            int2 new_mouse_position = (int2) { event.motion.x, event.motion.y };
            new_mouse_position.y = screen_dimensions.y - new_mouse_position.y;
            mouse->position = new_mouse_position;
            /*if (eventType == SDL_MOUSEBUTTONDOWN)
            {
                mouse->delta = (int2) { 0, 0 };
            }*/
            SDL_MouseButtonEvent *mouseEvent = &event.button;
            Uint8 button = mouseEvent->button;
            if (button == SDL_BUTTON_LEFT) {
                SetMouseKey(&mouse->left, eventType);
                /*if (eventType == SDL_MOUSEBUTTONDOWN)
                {
                    mouse_begin = mouse->position;
                    relative_mouse_2 = (int2) { 0, 0 };
                }*/
            } else if (button == SDL_BUTTON_MIDDLE) {
                SetMouseKey(&mouse->middle, eventType);
            } else if (button == SDL_BUTTON_RIGHT) {
                SetMouseKey(&mouse->right, eventType);
            }
        } else if (eventType == SDL_MOUSEWHEEL) {
            mouse->wheel = (int2) { event.wheel.x, event.wheel.y };
        }
        ecs_modified(world, mouse_entity, Mouse);
    }
}