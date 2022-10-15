//! Render 2D entities.
void DestroyInTimeSystem(ecs_iter_t *it)
{
    double deltaTime = it->delta_time;
    DestroyInTime *destroyInTimes = ecs_field(it, DestroyInTime, 1);
    for (int i = 0; i < it->count; i++)
    {
        DestroyInTime *destroyInTime = &destroyInTimes[i];
        destroyInTime->value -= deltaTime;
        if (destroyInTime->value < 0)
        {
            ecs_delete(it->world, it->entities[i]);
        }
    }
}
ECS_SYSTEM_DECLARE(DestroyInTimeSystem);