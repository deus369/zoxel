//! Closes the game when button is clicked.
void ExitGameButtonSystem(ecs_iter_t *it)
{
    // printf("WindowCloseSystem [%i]\n", it->count);
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++)
    {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1)
        {
            exit_game();
        }
    }
}
ECS_SYSTEM_DECLARE(ExitGameButtonSystem);