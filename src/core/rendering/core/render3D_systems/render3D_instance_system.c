extern void RenderEntity3D(float3 position, float4 rotation, float scale1D, float brightness);

void InstanceRender3DSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        // printf("    Bob's Position2D is {%f, %f}\n", position.value.x, position.value.y);
        RenderEntity3D(position->value, rotation->value, scale1D->value, brightness->value);
    }
}
zoxel_declare_system(InstanceRender3DSystem)