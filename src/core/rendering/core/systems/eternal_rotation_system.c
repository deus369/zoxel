//! Rotates things eternally.
void EternalRotationSystem(ecs_iter_t *it)
{
    // float deltaTime = (float) it->delta_time;
    Rotation3D *rotations = ecs_field(it, Rotation3D, 1);
    const EternalRotation *eternalRotations = ecs_field(it, EternalRotation, 2);
    for (int i = 0; i < it->count; i++)
    {
        const EternalRotation *eternalRotation = &eternalRotations[i];
        Rotation3D *rotation = &rotations[i];
        rotation->value = quaternion_rotate(eternalRotation->value, rotation->value);
        // printf("Rotation3D: %f %f %f %f\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
    }
}
zoxel_declare_system(EternalRotationSystem)

// float4 rotationValue = ; // float4_multiply_float(eternalRotation->value, deltaTime);