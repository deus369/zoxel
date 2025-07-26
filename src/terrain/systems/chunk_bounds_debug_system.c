extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void ChunkBoundsDrawSystem(ecs_iter_t *it) {
    const color_rgb up_color = (color_rgb) { 0, 0, 255 };
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(ChunkSize)
    zox_sys_in(VoxScale)
    zox_sys_in(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(Position3D, position3D)
        zox_sys_i(ChunkSize, chunkSize)
        zox_sys_i(VoxScale, voxScale)
        if (renderDisabled->value) {
            continue;
        }
        const bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        // zox_log("chunk_bounds %fx%fx%f - %fx%fx%f\n", chunk_bounds.center.x, chunk_bounds.center.y, chunk_bounds.center.z, chunk_bounds.extents.x, chunk_bounds.extents.y, chunk_bounds.extents.z)
        color_rgb line_color = up_color;
        //if (renderDisabled->value) line_color = up_color_disabled;
        spawn_cube_lines(world, chunk_bounds.center, chunk_bounds.extents, 1, 1, line_color);
        // render_line3D(world, chunk_bounds.center, float3_add(chunk_bounds.center, float3_up), line_color);
        render_line3D(world, float3_add(chunk_bounds.center, float3_down), float3_add(chunk_bounds.center, float3_up), line_color);
        render_line3D(world, float3_add(chunk_bounds.center, float3_left), float3_add(chunk_bounds.center, float3_right), line_color);

        render_line3D(world, float3_add(chunk_bounds.center, (float3) { 0, 0, -chunk_bounds.extents.z}), float3_add(chunk_bounds.center, (float3) { 0, 0, chunk_bounds.extents.z}), line_color);
        render_line3D(world, float3_add(chunk_bounds.center, (float3) { -chunk_bounds.extents.x, 0, 0 }), float3_add(chunk_bounds.center, (float3) { chunk_bounds.extents.x, 0, 0 }), line_color);
    }
} zox_declare_system(ChunkBoundsDrawSystem)
