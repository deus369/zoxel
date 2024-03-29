void DestroyInTimeSystem(ecs_iter_t *it) {
    zox_iter_world()
    double delta_time = zox_delta_time;
    DestroyInTime *destroyInTimes = ecs_field(it, DestroyInTime, 1);
    for (int i = 0; i < it->count; i++) {
        DestroyInTime *destroyInTime = &destroyInTimes[i];
        if (!destroyInTime->value) continue;
        destroyInTime->value -= delta_time;
        if (destroyInTime->value <= 0) zox_delete(it->entities[i])
    }
} zox_declare_system(DestroyInTimeSystem)
