// a simple idle scale animation
void OscillateSystem(ecs_iter_t *it) {
    // const float addition = 0.032f;
    const float speed = 1.0f;
    const double time = zox_current_time;
    zox_sys_begin()
    zox_sys_in(OscillateStartPosition3D)
    zox_sys_in(OscillateDeltaPosition3D)
    zox_sys_out(LocalPosition3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(OscillateStartPosition3D, oscillateStartPosition3D)
        zox_sys_i(OscillateDeltaPosition3D, oscillateDeltaPosition3D)
        zox_sys_o(LocalPosition3D, localPosition)
        const double animation_time = time; // - animationStart->value;
        localPosition->value.x = oscillateStartPosition3D->value.x + oscillateDeltaPosition3D->value.x * sin(animation_time * speed);
        localPosition->value.y = oscillateStartPosition3D->value.y + oscillateDeltaPosition3D->value.y * sin(animation_time * speed);
        localPosition->value.z = oscillateStartPosition3D->value.z + oscillateDeltaPosition3D->value.z * sin(animation_time * speed);
    }
} zoxd_system(OscillateSystem)