// extern void zox_debug_sound(ecs_world_t* world, ecs_entity_t e);

void DestroyInTimeSystem(ecs_iter_t *it) {
    init_delta_time()
    const float max_delta = 0.1f;  // 100 ms max step, tweak as needed
    float dt = delta_time > max_delta ? max_delta : delta_time;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_out(DestroyInTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_o(DestroyInTime, destroyInTime)
        if (!destroyInTime->value) {
            continue;
        }
        destroyInTime->value -= dt;
        if (destroyInTime->value <= 0) {
            // zox_debug_sound(world, e);
            zox_delete(e);
        }
    }
} zox_declare_system(DestroyInTimeSystem)