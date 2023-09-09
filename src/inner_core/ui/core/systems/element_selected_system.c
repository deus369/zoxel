//! Changes brightness based on raycast state.
void ElementSelectedSystem(ecs_iter_t *it) {
    const SelectState *selectableStates = ecs_field(it, SelectState, 2);
    Brightness *brightness = ecs_field(it, Brightness, 3);
    for (int i = 0; i < it->count; i++) {
        const SelectState *selectState = &selectableStates[i];
        if (selectState->value == 1) {
            brightness->value = 1.18f;
        } else {
            brightness->value = 0.85f;
        }
    }
}
zox_declare_system(ElementSelectedSystem)