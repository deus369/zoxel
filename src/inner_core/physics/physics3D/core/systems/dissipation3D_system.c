const float friction_threshold = 0.001f;
const float rotation_friction = 8.0f;

float4 calculate_dissipation(const float4 omega3D) {
    // the rotational velocity quaternion
    float mag = sqrt(omega3D.x * omega3D.x + omega3D.y * omega3D.y + omega3D.z * omega3D.z + omega3D.w * omega3D.w);
    if (mag < friction_threshold) {
        return quaternion_identity;
    }
    // Calculate the friction factor
    float factor = rotation_friction * mag / (mag * mag + 1e-6);
    // Apply friction to each component of the quaternion
    float4 dissipation = {
        .w = omega3D.w * factor,
        .x = omega3D.x * factor,
        .y = omega3D.y * factor,
        .z = omega3D.z * factor
    };
    // quaternion_normalize(&dissipation);
    return dissipation;
}

void Dissipation3DSystem(ecs_iter_t *it) {
    const Omega3D *omega3Ds = ecs_field(it, Omega3D, 2);
    Alpha3D *apha3Ds = ecs_field(it, Alpha3D, 3);
    for (int i = 0; i < it->count; i++) {
        const Omega3D *omega3D = &omega3Ds[i];
        Alpha3D *alpha3D = &apha3Ds[i];
        quaternion_rotate_quaternion_p(&alpha3D->value, calculate_dissipation(omega3D->value));
        // zoxel_log("omega is dissipating\n");
    }
}
zoxel_declare_system(Dissipation3DSystem)

/*float norm = sqrt(pow(alpha3D.x, 2) + pow(alpha3D.y, 2) + pow(alpha3D.z, 2) + pow(alpha3D.w, 2));
// float norm = sqrt(pow(omega3D.x, 2) + pow(omega3D.y, 2) + pow(omega3D.z, 2) + pow(omega3D.w, 2));
dissipation.x /= norm;
dissipation.y /= norm;
dissipation.z /= norm;
dissipation.w /= norm;*/

    /*
    // Calculate the amount of friction to apply
    float friction = rotation_friction * mag;
    // If the magnitude of the rotational velocity quaternion is below the friction threshold, set it to zero
    float4 dissipation = quaternion_identity;
    // Calculate the scalar part of the quaternion for the friction calculation
    float scalar = sqrt(1 - pow(omega3D.w, 2));
    // Calculate the amount of friction to apply to the scalar part of the quaternion
    float scalarFriction = friction * scalar;
    // Calculate the amount of friction to apply to the vector part of the quaternion
    float vectorFriction = friction * sqrt(pow(omega3D.x, 2) + pow(omega3D.y, 2) + pow(omega3D.z, 2));
    // Apply friction to the scalar part of the quaternion
    dissipation.w = scalarFriction * omega3D.w / mag;
    // Apply friction to the vector part of the quaternion
    float factor = vectorFriction / mag;
    dissipation.x += factor * omega3D.x;
    dissipation.y += factor * omega3D.y;
    dissipation.z += factor * omega3D.z;*/

/*float4 calculate_dissipation(const float4 omega3D) {
    // the rotational velocity quaternion
    float mag = sqrt(pow(omega3D.x, 2) + pow(omega3D.y, 2) + pow(omega3D.z, 2) + pow(omega3D.w, 2));
    // Calculate the amount of friction to apply
    float friction = rotation_friction * mag;
    // If the magnitude of the rotational velocity quaternion is below the friction threshold, set it to zero
    if (mag < friction_threshold) {
        return quaternion_identity;
    }
    // float4 dissipation = quaternion_identity;
    // Calculate the axis-angle representation of the rotation
    float axisX = omega3D.x / mag;
    float axisY = omega3D.y / mag;
    float axisZ = omega3D.z / mag;
    float angle = 2.0f * atan2f(sqrtf(omega3D.x * omega3D.x + omega3D.y * omega3D.y + omega3D.z * omega3D.z), omega3D.w);
    // Correct the axis-angle representation if necessary
    const float pi = 3.14159265358979323846f;
    const float eps = 0.0001f;
    if (fabsf(axisX) < eps && fabsf(axisY) < eps) {
        if (axisZ > 0.0f) {
            angle = pi - angle;
        } else {
            angle = -pi + angle;
        }
        axisX = sinf(angle * 0.5f);
        axisY = 0.0f;
        axisZ = cosf(angle * 0.5f);
    }
    // Apply friction to the axis-angle representation
    angle = fmaxf(angle - friction, 0.0f);
    // Convert the axis-angle representation back to a quaternion
    float4 dissipation;
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    dissipation.x = axisX * s;
    dissipation.y = axisY * s;
    dissipation.z = axisZ * s;
    dissipation.w = c;
    return dissipation;
}*/