void set_position_from_parents(ecs_world_t *world, ecs_entity_t parent, float3 *position3D, float3 local_position3D) {
    float3 parent_position = zox_get_value(parent, Position3D)
    float4 parent_rotation = zox_get_value(parent, Rotation3D)
    *position3D = local_position3D;
    float4_rotate_float3_p(parent_rotation, position3D);
    float3_add_float3_p(position3D, parent_position);
}

void ParentPositionSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 1);
    const LocalPosition3D *localPosition3Ds = ecs_field(it, LocalPosition3D, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    for (int i = 0; i < it->count; i++) {
        const ParentLink *parentLink = &parentLinks[i];
        if (!ecs_is_valid(world, parentLink->value)) continue;
        const LocalPosition3D *localPosition3D = &localPosition3Ds[i];
        Position3D *position3D = &position3Ds[i];
        set_position_from_parents(world, parentLink->value, &position3D->value, localPosition3D->value);
    }
} zox_declare_system(ParentPositionSystem)
