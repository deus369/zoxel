//! Resets EntityDirty after one frame.
void EntityDirtyResetSystem(ecs_iter_t *it)
{
    if (!ecs_query_changed(NULL, it))
    {
        return;
    }
    EntityDirty *entityDirtys = ecs_field(it, EntityDirty, 1);
    for (int i = 0; i < it->count; i++)
    {
        EntityDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value == 1)
        {
            entityDirty->value = 0;
            // printf("EntityDirty Reseting!\n");
        }
    }
}
ECS_SYSTEM_DECLARE(EntityDirtyResetSystem);