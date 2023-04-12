const double rotate_power = 0.5f;
const float angleScale = 0.005f;
const float axisThreshold = 0.01f;
// maybe if switch direction, do a velocity (omega3D) change?
    
float4 mouse_delta_to_rotation(float deltaX, float deltaY) {
    float4 output = quaternion_identity;
    output.x = deltaX;
    output.y = deltaY;
    quaternion_normalize(&output);
    return output;
}

void Player3DRotateSystem(ecs_iter_t *it) {
    ecs_query_t *playerCharacterQuery = it->ctx;
    ecs_iter_t playerCharacterIterator = ecs_query_iter(it->world, playerCharacterQuery);
    ecs_query_next(&playerCharacterIterator);
    if (playerCharacterIterator.count == 0) {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    Alpha3D *alpha3Ds = ecs_field(&playerCharacterIterator, Alpha3D, 2);
    const DisableMovement *disableMovements = ecs_field(&playerCharacterIterator, DisableMovement, 3);
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        float3 euler = { 0, -mouse->delta.x };
        if (!(euler.x == 0 && euler.y == 0)) {
            euler.x *= rotate_power;
            euler.y *= rotate_power;
            float4 quaternion = mouse_delta_to_rotation(euler.x, euler.y);
            for (int j = 0; j < playerCharacterIterator.count; j++) {
                const DisableMovement *disableMovement = &disableMovements[j];
                if (disableMovement->value) {
                    continue;
                }
                Alpha3D *alpha3D = &alpha3Ds[j];
                quaternion_rotate_quaternion_p(&alpha3D->value, quaternion);
            }
        }
    }
}
zoxel_declare_system(Player3DRotateSystem)

// const Rotation3D *rotation3D = &rotation3Ds[j];
// float4 rotation = quaternion_from_euler(euler);
//! \todo Link directly to player characters from player.
// const float2 maxVelocity = { 12.6f, 12.6f };
// quaternion_rotate_quaternion_p(&alpha3D->value, mouse_delta_to_rotation(euler.x, euler.y));
/*float4 player_rotate = quaternion_identity;
player_rotate.y = rotate_power;
// player_rotate.y = mouse->delta.x * rotate_power;
if (euler.y > 0) player_rotate.y = rotate_power;
if (euler.y < 0) player_rotate.y = -rotate_power;
quaternion_rotate_quaternion_p(&alpha3D->value, player_rotate);*/

/*
// Step 1: Calculate the magnitude of the mouse delta
float magnitude = sqrt(euler.x * euler.x + euler.y * euler.y);
// Step 2: Calculate the rotation axis
float axisX = euler.x;
float axisY = euler.y;
float axisZ = 0.0f;
// Step 3: Normalize the rotation axis
float axisMagnitude = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
if (axisMagnitude < 0.00001f) {
    // The mouse delta is too small, so there is no rotation
    continue;
}
axisX /= axisMagnitude;
axisY /= axisMagnitude;
axisZ /= axisMagnitude;
// Step 4: Calculate the rotation angle
float angle = magnitude;
// Step 5: Convert the axis-angle representation into a quaternion
float sinAngle = sin(angle / 2.0f);
float cosAngle = cos(angle / 2.0f);
float4 player_rotate;
player_rotate.x = axisX * sinAngle;
player_rotate.y = axisY * sinAngle;
player_rotate.z = axisZ * sinAngle;
player_rotate.w = cosAngle;
// Step 6: Normalize the resulting quaternion
float mag = sqrt(alpha3D->value.x * alpha3D->value.x + alpha3D->value.y * alpha3D->value.y + alpha3D->value.z * alpha3D->value.z + alpha3D->value.w * alpha3D->value.w);
player_rotate.x /= mag;
player_rotate.y /= mag;
player_rotate.z /= mag;
player_rotate.w /= mag;
quaternion_rotate_quaternion_p(&alpha3D->value, player_rotate);
*/
// quaternion_rotate_quaternion_p(&alpha3D->value, rotation);
// alpha3D->value.y = euler.y;
/*const Rotation3D *rotation3D = &rotation3Ds[j];
const Velocity3D *velocity3D = &velocity3Ds[j];
float3 rotated_movement = float4_rotate_float3(rotation3D->value, movement);
float3 rotated_velocity = float4_rotate_float3(float4_inverse(rotation3D->value), velocity3D->value);
// todo: get rotated velocity to test max
if (rotated_movement.x > 0 && rotated_velocity.x < maxVelocity.x) {
    acceleration3D->value.x += rotated_movement.x;
} else if (rotated_movement.x < 0 && rotated_velocity.x > -maxVelocity.x) {
    acceleration3D->value.x += rotated_movement.x;
}
acceleration3D->value.y += rotated_movement.y;
if (rotated_movement.z > 0 && rotated_velocity.z < maxVelocity.y) {
    acceleration3D->value.z += rotated_movement.z;
} else if (rotated_movement.z < 0 && rotated_velocity.z > -maxVelocity.y) {
    acceleration3D->value.z += rotated_movement.z;
}*/
    // const Velocity3D *velocity3Ds = ecs_field(&playerCharacterIterator, Velocity3D, 3);
    // const Rotation3D *rotation3Ds = ecs_field(&playerCharacterIterator, Rotation3D, 4);
    // const Rotation3D *rotation3Ds = ecs_field(&playerCharacterIterator, Rotation3D, 5);
    /*float axisX = deltaY;
    float axisY = -deltaX;
    float axisZ = 0.0f;
    // Compute the length of the rotation axis
    float axisLength = sqrtf(axisX * axisX + axisY * axisY + axisZ * axisZ);
    // Normalize the rotation axis
    if (axisLength > 0.0f) {
        axisX /= axisLength;
        axisY /= axisLength;
        axisZ /= axisLength;
    }
    // Compute the rotation angle
    float angle = axisLength * rotate_power; // angleScale;
    // Check for the axis-angle plane
    float dotProduct = fabsf(axisZ);
    if (dotProduct > axisThreshold) {
        // Rotate around the z-axis instead
        axisX = 0.0f;
        axisY = 0.0f;
        axisZ = 1.0f;
        angle *= axisZ > 0.0f ? -1.0f : 1.0f;
    }
    // Convert the rotation axis and angle to a quaternion
    float sinAngle = sinf(angle * 0.5f);
    float cosAngle = cosf(angle * 0.5f);
    float4 output;
    output.x = axisX * sinAngle;
    output.y = axisY * sinAngle;
    output.z = axisZ * sinAngle;
    output.w = cosAngle;*/