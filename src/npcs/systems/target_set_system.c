void ThreatPositionSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(LastDamager)
    zox_sys_out(ThreatPosition)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LastDamager, lastDamager)
        zox_sys_o(ThreatPosition, threatPosition)
        if (zox_valid(lastDamager->value)) {
            zox_geter(lastDamager->value, Position3D, target)
            threatPosition->value = target->value;
            if (is_debug_target) {
                zox_geter_value(it->entities[i], Position3D, float3, position)
                debug_linec(world, position, threatPosition->value, color_rgb_gray);
            }
        }
    }
} zox_declare_system(ThreatPositionSystem)