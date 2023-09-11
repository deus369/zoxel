void ParentPositionSystem(ecs_iter_t *it) {
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 1);
    const LocalPosition3D *localPosition3Ds = ecs_field(it, LocalPosition3D, 2);
    Position3D *position3Ds = ecs_field(it, Position3D, 3);
    for (int i = 0; i < it->count; i++) {
        const ParentLink *parentLink = &parentLinks[i];
        if (!ecs_is_valid(world, parentLink->value)) continue;
        const LocalPosition3D *localPosition3D = &localPosition3Ds[i];
        Position3D *position3D = &position3Ds[i];
        float4 parent_rotation = ecs_get(world, parentLink->value, Rotation3D)->value;
        float3 parent_position = ecs_get(world, parentLink->value, Position3D)->value;
        position3D->value = localPosition3D->value;
        float4_rotate_float3_p(parent_rotation, &position3D->value);
        float3_add_float3_p(&position3D->value, parent_position);
    }
} zox_declare_system(ParentPositionSystem)