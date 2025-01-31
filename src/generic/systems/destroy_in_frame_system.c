void DestroyInFrameSystem(ecs_iter_t *it) {
    zox_iter_world()
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_delete(e)
    }
} zox_declare_system(DestroyInFrameSystem)
