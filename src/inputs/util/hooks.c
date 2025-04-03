zox_define_hook(key_down, (ecs_world_t* world, int32_t keycode), (world, keycode))

/*
 * zox_event_type(keyevent, void, ecs_world_t*, int32_t)
 * zoxel_dynamic_array(keyevent)
 * keyevent_array_d* functions_key_down;
 *
 * void initialize_functions_key_down() {
 *    functions_key_down = create_keyevent_array_d(initial_dynamic_array_size);
 * }
 *
 * void dispose_functions_key_down() {
 *    dispose_keyevent_array_d(functions_key_down);
 * }
 *
 * void add_functions_key_down(void (*event)(ecs_world_t *, int32_t)) {
 *    keyevent fun_event = (keyevent) { event };
 *    add_to_keyevent_array_d(functions_key_down, fun_event);
 * }
 *
 * void run_function_key_down(int i, ecs_world_t *world, int32_t keycode) {
 *    if (functions_key_down->data[i].value != NULL) {
 *        (*functions_key_down->data[i].value)(world, keycode);
 *    }
 * }
 *
 * void run_functions_key_down(ecs_world_t *world, int32_t keycode) {
 *    // zox_log("run functions for key down: %i - size %i\n", keycode, functions_key_down->size)
 *    for (int i = 0; i < functions_key_down->size; i++) {
 *        run_function_key_down(i, world, keycode);
 *    }
 * }*/
