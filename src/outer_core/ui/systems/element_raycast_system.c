//! A system that casts a ray into the ui elements.
/**
 * Creates an external event when selects a entity. Can be used by AI to select ui too.
*/
void ElementRaycastSystem(ecs_iter_t *it)
{
    // float deltaTime = (float) it->delta_time;
    /*Rotation *rotations = ecs_field(it, Rotation, 1);
    const EternalRotation *eternalRotations = ecs_field(it, EternalRotation, 2);
    for (int i = 0; i < it->count; i++)
    {
        Rotation *rotation = &rotations[i];
        const EternalRotation *eternalRotation = &eternalRotations[i];
        float4 rotationValue = eternalRotation->value; // float4_multiply_float(eternalRotation->value, deltaTime);
        rotation->value = quaternion_rotate(rotationValue, rotation->value);
        // printf("Rotation: %f %f %f %f\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
    }*/
}
ECS_SYSTEM_DECLARE(ElementRaycastSystem);