void DestroyInFrameSystem(ecs_iter_t *it) {
    zox_sys_world()
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_delete(e)
    }
} zox_declare_system(DestroyInFrameSystem)
