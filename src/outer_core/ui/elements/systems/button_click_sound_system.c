//! Plays a Sound when button is clicked
void ButtonClickSoundSystem(ecs_iter_t *it)
{
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++)
    {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1)
        {
            spawn_sound(it->world);
        }
    }
}
ECS_SYSTEM_DECLARE(ButtonClickSoundSystem);