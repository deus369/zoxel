void ChunkBoundsDebugSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkSize, chunkSizes, 2)
    zox_field_in(VoxScale, voxScales, 3)
    zox_field_in(RenderDisabled, renderDisableds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(ChunkSize, chunkSizes, chunkSize)
        zox_field_i_in(VoxScale, voxScales, voxScale)
        const bounds chunk_bounds = calculate_chunk_bounds(position3D->value, chunkSize->value, voxScale->value);
        spawn_cube_lines(world, chunk_bounds.center, chunk_bounds.extents, 1, 0.1, (color_rgb) { 0, 0, 126 });
        // zox_log("chunk_bounds %fx%fx%f - %fx%fx%f\n", chunk_bounds.center.x, chunk_bounds.center.y, chunk_bounds.center.z, chunk_bounds.extents.x, chunk_bounds.extents.y, chunk_bounds.extents.z)
    }
} zox_declare_system(ChunkBoundsDebugSystem)
