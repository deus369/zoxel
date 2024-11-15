// a simple idle scale animation
void OscillateSystem(ecs_iter_t *it) {
    const float addition = 0.016f;
    const float speed = 1.0f;
    const double time = zox_current_time;
    zox_field_out(LocalPosition3D, localPositions, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(LocalPosition3D, localPositions, localPosition)
        const double animation_time = time; // - animationStart->value;
        float position_y = test_bone_position + addition * sin(animation_time * speed);
        localPosition->value.y = position_y;
    }
} zox_declare_system(OscillateSystem)
