const float friction_threshold = 0.001f;
const float rotation_friction = 2.0f;

void Dissipation3DSystem(ecs_iter_t *it) {
    const Omega3D *omega3Ds = ecs_field(it, Omega3D, 2);
    Alpha3D *apha3Ds = ecs_field(it, Alpha3D, 3);
    for (int i = 0; i < it->count; i++) {
        const Omega3D *omega3D = &omega3Ds[i];
        Alpha3D *alpha3D = &apha3Ds[i];
        // the rotational velocity quaternion
        float mag = sqrt(pow(omega3D->value.x, 2) + pow(omega3D->value.y, 2) + pow(omega3D->value.z, 2) + pow(omega3D->value.w, 2));
        // Calculate the amount of friction to apply
        float friction = rotation_friction * mag;
        // If the magnitude of the rotational velocity quaternion is below the friction threshold, set it to zero
        if (mag < friction_threshold) {
            continue;
        }
        float4 dissipation = quaternion_identity;
        // Calculate the scalar part of the quaternion for the friction calculation
        float scalar = sqrt(1 - pow(omega3D->value.w, 2));
        // Calculate the amount of friction to apply to the scalar part of the quaternion
        float scalarFriction = friction * scalar;
        // Calculate the amount of friction to apply to the vector part of the quaternion
        float vectorFriction = friction * sqrt(pow(omega3D->value.x, 2) + pow(omega3D->value.y, 2) + pow(omega3D->value.z, 2));
        // Apply friction to the scalar part of the quaternion
        dissipation.w += scalarFriction * omega3D->value.w / mag;
        // Apply friction to the vector part of the quaternion
        float factor = vectorFriction / mag;
        dissipation.x += factor * omega3D->value.x;
        dissipation.y += factor * omega3D->value.y;
        dissipation.z += factor * omega3D->value.z;
        // Normalize the resulting quaternion
        float norm = sqrt(pow(alpha3D->value.x, 2) + pow(alpha3D->value.y, 2) + pow(alpha3D->value.z, 2) + pow(alpha3D->value.w, 2));
        dissipation.x /= norm;
        dissipation.y /= norm;
        dissipation.z /= norm;
        dissipation.w /= norm;
        quaternion_rotate_quaternion_p(&alpha3D->value, dissipation);
        // zoxel_log("omega is dissipating\n");
    }
}
zoxel_declare_system(Dissipation3DSystem)