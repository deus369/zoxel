//! Changes brightness based on raycast state.
void ElementSelectedSystem(ecs_iter_t *it) {
    const SelectableState *selectableStates = ecs_field(it, SelectableState, 2);
    Brightness *brightness = ecs_field(it, Brightness, 3);
    for (int i = 0; i < it->count; i++) {
        const SelectableState *selectableState = &selectableStates[i];
        if (selectableState->value == 1) {
            brightness->value = 1.18f;
        } else {
            brightness->value = 0.85f;
        }
    }
}
zoxel_declare_system(ElementSelectedSystem)