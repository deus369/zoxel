void set_rotation_from_parents(ecs_world_t *world, ecs_entity_t parent, float4 *rotation3D, float4 local_rotation3D) {
    float4 parent_rotation = ecs_get(world, parent, Rotation3D)->value;
    *rotation3D = parent_rotation;
    quaternion_rotate_quaternion_p(rotation3D, local_rotation3D);
}

void ParentRotationSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 1);
    const LocalRotation3D *localRotation3Ds = ecs_field(it, LocalRotation3D, 2);
    Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    for (int i = 0; i < it->count; i++) {
        const ParentLink *parentLink = &parentLinks[i];
        if (!ecs_is_valid(world, parentLink->value)) continue;
        const LocalRotation3D *localRotation3D = &localRotation3Ds[i];
        Rotation3D *rotation3D = &rotation3Ds[i];
        set_rotation_from_parents(world, parentLink->value, &rotation3D->value, localRotation3D->value);
        // rotation3D->value = ecs_get(world, parentLink->value, Rotation3D)->value;
        // quaternion_rotate_quaternion_p(&rotation3D->value, localRotation3D->value);
    }
} zox_declare_system(ParentRotationSystem)