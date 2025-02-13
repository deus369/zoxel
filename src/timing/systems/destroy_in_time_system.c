void DestroyInTimeSystem(ecs_iter_t *it) {
    zox_field_world()
    init_delta_time()
    zox_field_out(DestroyInTime, destroyInTimes, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(DestroyInTime, destroyInTimes, destroyInTime)
        if (!destroyInTime->value) continue;
        destroyInTime->value -= delta_time;
        if (destroyInTime->value <= 0) {
            zox_field_e()
            zox_delete(e)
        }
    }
} zox_declare_system(DestroyInTimeSystem)
