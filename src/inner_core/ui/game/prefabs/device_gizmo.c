// grid like ui
const float device_gizmo_fade_time = 3;

ecs_entity_t spawn_prefab_device_gizmo(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_set(e, DestroyInTime, { device_gizmo_fade_time })
    zox_prefab_add_animation_event(world, e, device_gizmo_fade_time);
    return e;
}

// when switch, spawn, destroy after x seconds, add a cooldown on switching devices
ecs_entity_t spawn_device_gizmo(ecs_world_t *world, const ecs_entity_t canvas, const unsigned char device_type) {
    const unsigned char size = 64;
    const unsigned char position_offset = 16;
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    SpawnIcon spawnIcon = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = canvas,
            .position = int2_half(canvas_size),
            .size = canvas_size
        },
        .element = {
            .prefab = prefab_device_gizmo,
            .size = int2_single(size),
            .position = (int2) { position_offset, position_offset },
            .anchor = float2_zero,
            .layer = 1,
        },
        .texture_size = int2_single(size),
    };
    const ecs_entity_t e = spawn_icon(world, &spawnIcon);
    if (device_type == zox_device_mode_gamepad) {
        clone_texture_to_entity(world, e, "device_gamepad");
    } else if (device_type == zox_device_mode_keyboardmouse) {
        clone_texture_to_entity(world, e, "device_keyboard");
    } else if (device_type == zox_device_mode_touchscreen) {
        clone_texture_to_entity(world, e, "device_touchscreen");
    } else {
        clone_texture_to_entity(world, e, "device_none");
    }
    zox_set(e, AnimationStart, { zox_current_time })
    return e;
}
