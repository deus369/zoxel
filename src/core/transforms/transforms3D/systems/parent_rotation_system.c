void ParentRotationSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ParentLink, parentLinks, 1)
    zox_field_in(LocalRotation3D, localRotation3Ds, 2)
    zox_field_out(Rotation3D, rotation3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        if (!zox_valid(parentLink->value)) continue;
        zox_field_i_in(LocalRotation3D, localRotation3Ds, localRotation3D)
        zox_field_i_out(Rotation3D, rotation3Ds, rotation3D)
        set_rotation_from_parents(world, parentLink->value, &rotation3D->value, localRotation3D->value);
    }
} zox_declare_system(ParentRotationSystem)
