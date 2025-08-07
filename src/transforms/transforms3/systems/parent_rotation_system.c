void ParentRotationSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ParentLink)
    zox_sys_in(LocalRotation3D)
    zox_sys_out(Rotation3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ParentLink, parentLink)
        zox_sys_i(LocalRotation3D, localRotation3D)
        zox_sys_o(Rotation3D, rotation3D)
        if (!zox_valid(parentLink->value)) {
            continue;
        }
        set_rotation_from_parents(world, parentLink->value, &rotation3D->value, localRotation3D->value);
    }
} zox_declare_system(ParentRotationSystem)