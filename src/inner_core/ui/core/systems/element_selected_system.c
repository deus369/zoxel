//! Changes brightness based on raycast state.
void ElementSelectedSystem(ecs_iter_t *it) {
    const SelectState *selectableStates = ecs_field(it, SelectState, 2);
    Brightness *brightnesss = ecs_field(it, Brightness, 3);
    for (int i = 0; i < it->count; i++) {
        const SelectState *selectState = &selectableStates[i];
        Brightness *brightness = &brightnesss[i];
        if (selectState->value) brightness->value = ui_selected_brightness;
        else brightness->value = ui_default_brightness;
    }
} zox_declare_system(ElementSelectedSystem)
