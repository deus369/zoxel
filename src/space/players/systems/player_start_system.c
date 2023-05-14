/*void PlayerPlayButtonSystem(ecs_iter_t *it) {
    ecs_query_t *query = it->ctx;
    ecs_iter_t iter2 = ecs_query_iter(it->world, query);
    ecs_query_next(&iter2);
    if (iter2.count == 0) {
        return;
    }
    ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    const Gamepad *gamepads = ecs_field(&iter2, Gamepad, 1);
    for (int i = 0; i < it->count; i++) {
        ClickableState *clickableState = &clickableStates[i];
        for (int j = 0; j < iter2.count; j++) {
            const Gamepad *gamepad = &gamepads[j];
            if (gamepad->start.pressed_this_frame) {
                zoxel_log(" > shortcutting to starting game\n");
                clickableState->value = 1;
                break;
            }

        }
    }
}
zox_declare_system(PlayerPlayButtonSystem)*/
