void ParentPositionSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ParentLink)
    zox_sys_in(LocalPosition3D)
    zox_sys_out(Position3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(LocalPosition3D, localPosition3D)
        zox_sys_o(Position3D, position3D)
        if (!zox_valid(parentLink->value)) {
            continue;
        }
        set_position_from_parents(world, parentLink->value, &position3D->value, localPosition3D->value);
    }
} zoxd_system(ParentPositionSystem)
