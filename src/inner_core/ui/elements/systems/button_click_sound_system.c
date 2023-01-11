//! Plays a Sound when button is clicked
void ButtonClickSoundSystem(ecs_iter_t *it)
{
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++)
    {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1)
        {
            spawn_generated_sound(it->world,
                note_frequencies[42], 0.8 + 0.4 * (rand() % 101) / 100.0,
                instrument_edm);
        }
    }
}
zoxel_declare_system(ButtonClickSoundSystem)