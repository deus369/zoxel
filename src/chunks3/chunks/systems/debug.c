// show lines on quads along chunk edge
extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

void render_voxel_line(ecs_world_t* world,
    byte3 position,
    float scale,
    float3 chunk_position,
    const color_rgb c)
{
    float3 positionf = float3_add(
        chunk_position,
        (float3) {
            position.x * scale,
            position.y * scale,
            position.z * scale
        });
    // half voxel addition
    float3_add_float3_p(&positionf, (float3) { 0.25f, 0, 0.25f });
    float3 point_start = positionf;
    float3 point_end = float3_add(positionf, (float3) { 0, scale, 0 });
    render_line3D(world, point_start, point_end, c);
}

void ChunkDebugSystem(ecs_iter_t *it) {
    const byte debug_distance = 1;
    const color_rgb chunk_color = { 155, 0, 0 };
    const color_rgb voxel_color = { 0, 155, 155 };
    if (!is_render_chunk_edges) {
        return;
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderDistance)
    zox_sys_in(ChunkNeighbors)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        if (renderDistance->value > debug_distance) {
            continue;
        }
        // draw grid around chunk
        byte length = powers_of_two_byte[nodeDepth->value];
        float scale = get_terrain_voxel_scale(nodeDepth->value);
        const ecs_entity_t chunk_above = chunkNeighbors->value[direction_up];
        const VoxelNode* voxel_node_above = zox_valid(chunk_above) ? zox_gett(chunk_above, VoxelNode) : NULL;

        const float3 size = float3_single(8);
        const float3 draw_position = float3_add(position->value, float3_half(size));
        debug_cubec(world, draw_position, size, chunk_color);

        byte2 positionxz = byte2_zero;
        for (positionxz.x = 0; positionxz.x < length; positionxz.x++) {
            for (positionxz.y = 0; positionxz.y < length; positionxz.y++) {
                if (!byte2_on_edge(positionxz, byte2_single(length))) {
                    continue;
                }
                byte3 ground_position = find_position_on_ground(
                    voxelNode,
                    voxel_node_above,
                    nodeDepth->value,
                    positionxz
                );
                if (!byte3_equals(ground_position, byte3_full)) {
                    render_voxel_line(world,
                        ground_position,
                        scale,
                        position->value,
                        voxel_color);
                }
            }
        }
    }
} zox_declare_system(ChunkDebugSystem)