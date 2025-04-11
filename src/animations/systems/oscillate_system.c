// a simple idle scale animation
void OscillateSystem(ecs_iter_t *it) {
    const float addition = 0.032f;
    const float speed = 1.0f;
    const double time = zox_current_time;
    zox_field_in(OscillateStartPosition3D, oscillateStartPosition3Ds, 1)
    zox_field_out(LocalPosition3D, localPositions, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(OscillateStartPosition3D, oscillateStartPosition3Ds, oscillateStartPosition3D)
        zox_field_o(LocalPosition3D, localPositions, localPosition)
        const double animation_time = time; // - animationStart->value;
        float position_y = oscillateStartPosition3D->value.y + addition * sin(animation_time * speed);
        localPosition->value.y = position_y;
    }
} zox_declare_system(OscillateSystem)