void add_debug_cube(ecs_world_t* world, const ecs_entity_t e, const float3 size) {
    zox_prefab_set(e, DebugCubeLines, { 1 })
    zox_add_tag(e, CubeLines)
    zox_prefab_set(e, CubeLinesThickness, { 4 })
    zox_prefab_set(e, ColorRGB, {{ 0, 255, 255 }})
    zox_prefab_set(e, Bounds3D, { size })
    zox_prefab_set(e, RenderLod, { 0 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, MeshIndicies, { 0, NULL });
}

void debug_cubec(ecs_world_t* world, const float3 p, const float3 s, color_rgb c) {
    // Calculate the min and max corners
    float3 min = {
        p.x - s.x * 0.5f,
        p.y - s.y * 0.5f,
        p.z - s.z * 0.5f
    };
    float3 max = {
        p.x + s.x * 0.5f,
        p.y + s.y * 0.5f,
        p.z + s.z * 0.5f
    };

    // Bottom square
    float3 a = {min.x, min.y, min.z};
    float3 b = {max.x, min.y, min.z};
    float3 c_ = {max.x, min.y, max.z};
    float3 d = {min.x, min.y, max.z};

    // Top square
    float3 e = {min.x, max.y, min.z};
    float3 f = {max.x, max.y, min.z};
    float3 g = {max.x, max.y, max.z};
    float3 h = {min.x, max.y, max.z};

    // Bottom edges
    debug_linec(world, a, b, c);
    debug_linec(world, b, c_, c);
    debug_linec(world, c_, d, c);
    debug_linec(world, d, a, c);

    // Top edges
    debug_linec(world, e, f, c);
    debug_linec(world, f, g, c);
    debug_linec(world, g, h, c);
    debug_linec(world, h, e, c);

    // Vertical edges
    debug_linec(world, a, e, c);
    debug_linec(world, b, f, c);
    debug_linec(world, c_, g, c);
    debug_linec(world, d, h, c);
}
