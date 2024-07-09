void ParentPositionSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ParentLink, parentLinks, 1)
    zox_field_in(LocalPosition3D, localPosition3Ds, 2)
    zox_field_out(Position3D, position3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ParentLink, parentLinks, parentLink)
        if (!zox_valid(parentLink->value)) continue;
        zox_field_i(LocalPosition3D, localPosition3Ds, localPosition3D)
        zox_field_o(Position3D, position3Ds, position3D)
        set_position_from_parents(world, parentLink->value, &position3D->value, localPosition3D->value);
    }
} zox_declare_system(ParentPositionSystem)
