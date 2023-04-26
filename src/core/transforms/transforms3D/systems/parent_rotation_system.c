void ParentRotationSystem(ecs_iter_t *it) {
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 1);
    const LocalRotation3D *localRotation3Ds = ecs_field(it, LocalRotation3D, 2);
    Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    for (int i = 0; i < it->count; i++) {
        const ParentLink *parentLink = &parentLinks[i];
        if (!ecs_is_valid(world, parentLink->value)) {
            continue;
        }
        const LocalRotation3D *localRotation3D = &localRotation3Ds[i];
        Rotation3D *rotation3D = &rotation3Ds[i];
        rotation3D->value = ecs_get(world, parentLink->value, Rotation3D)->value;
        quaternion_rotate_quaternion_p(&rotation3D->value, localRotation3D->value);
    }
}
zoxel_declare_system(ParentRotationSystem)