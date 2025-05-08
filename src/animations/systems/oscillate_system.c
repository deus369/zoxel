// a simple idle scale animation
void OscillateSystem(ecs_iter_t *it) {
    // const float addition = 0.032f;
    const float speed = 1.0f;
    const double time = zox_current_time;
    zox_field_in(OscillateStartPosition3D, oscillateStartPosition3Ds, 1)
    zox_field_in(OscillateDeltaPosition3D, oscillateDeltaPosition3Ds, 2)
    zox_field_out(LocalPosition3D, localPositions, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(OscillateStartPosition3D, oscillateStartPosition3Ds, oscillateStartPosition3D)
        zox_field_i(OscillateDeltaPosition3D, oscillateDeltaPosition3Ds, oscillateDeltaPosition3D)
        zox_field_o(LocalPosition3D, localPositions, localPosition)
        const double animation_time = time; // - animationStart->value;
        localPosition->value.x = oscillateStartPosition3D->value.x + oscillateDeltaPosition3D->value.x * sin(animation_time * speed);
        localPosition->value.y = oscillateStartPosition3D->value.y + oscillateDeltaPosition3D->value.y * sin(animation_time * speed);
        localPosition->value.z = oscillateStartPosition3D->value.z + oscillateDeltaPosition3D->value.z * sin(animation_time * speed);
    }
} zox_declare_system(OscillateSystem)