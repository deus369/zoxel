void DestroyInTimeSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(DestroyInTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_o(DestroyInTime, destroyInTime)
        if (!destroyInTime->value) {
            continue;
        }
        destroyInTime->value -= delta_time;
        if (destroyInTime->value <= 0) {
            zox_delete(e)
        }
    }
} zox_declare_system(DestroyInTimeSystem)