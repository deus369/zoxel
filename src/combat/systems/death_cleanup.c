extern double zox_current_time;
const double cleanup_time = 2.0;
// time after death, character will be removed
void DeathCleanSystem(ecs_iter_t *it) {
    const double time = zox_current_time;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Dead)
    zox_sys_in(DiedTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Dead, dead)
        zox_sys_i(DiedTime, diedTime)
        if (dead->value != zox_dirty_end) {
            continue;
        }
        if (time - diedTime->value >= cleanup_time) {
            zox_delete(e)
        }
    }
} zox_declare_system(DeathCleanSystem)