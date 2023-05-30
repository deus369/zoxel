void DestroyInTimeSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    double delta_time = zox_delta_time;
    DestroyInTime *destroyInTimes = ecs_field(it, DestroyInTime, 1);
    for (int i = 0; i < it->count; i++) {
        DestroyInTime *destroyInTime = &destroyInTimes[i];
        destroyInTime->value -= delta_time;
        if (destroyInTime->value < 0) zox_delete(it->entities[i])
    }
}
zox_declare_system(DestroyInTimeSystem)