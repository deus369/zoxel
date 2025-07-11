// show lines on quads along chunk edge
extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

// todo: traverse chunk VoxelNode
// todo: using neighbor voxels, perform a function at target depth
// todo: pass data in function
void traverse_chunk(TraverseChunk *data) {
    const color_rgb debug_color = { 155, 255, 125 };
    if (!data->chunk) {
        return;
    }
    if (data->depth != data->target_depth) {
        if (is_closed_VoxelNode(data->chunk)) {
            byte3 position_parent = data->position;
            byte3_multiply_byte(&position_parent, 2);
            byte node_size = powers_of_two_byte[data->depth];
            if (!byte3_on_edge_xz(position_parent, (byte3) { node_size, node_size, node_size })) {
                return;
            }
            // zox_log(" > depth [%i] line at position: %ix%ix%i\n", data->depth, data->position.x, data->position.y, data->position.z)
            float3 voxel_position = float3_add(data->chunk_position, (float3) { data->position.x * data->scale, data->position.y * data->scale, data->position.z * data->scale });
            float3_add_float3_p(&voxel_position, (float3) { 0.25f, 0, 0.25f }); // half voxel addition
            float3 point_start = voxel_position;
            float3 point_end = float3_add(voxel_position, (float3) { 0, 1.0f, 0 });
            render_line3D(data->world, point_start, point_end, debug_color);
            return; // if node is closed
        }
        const byte depth = data->depth + 1;
        // const byte dividor = powers_of_two_byte[depth - 1];
        const VoxelNode *node = data->chunk;
        byte3 position_parent = data->position;
        byte3_multiply_byte(&position_parent, 2);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            data->chunk = &kids[i];
            data->depth = depth;
            data->position = byte3_add(position_parent, octree_positions_b[i]);
            traverse_chunk(data);
        }
    } else {
        // only for edge voxels
        if (!byte3_on_edge_xz(data->position, (byte3) { 32, 32, 32 })) return;
        const color_rgb debug_color = { 255, 0, 0 };
        // zox_log(" > depth [%i] line at position: %ix%ix%i\n", data->depth, data->position.x, data->position.y, data->position.z)
        float3 voxel_position = float3_add(data->chunk_position, (float3) { data->position.x * data->scale, data->position.y * data->scale, data->position.z * data->scale });
        float3_add_float3_p(&voxel_position, (float3) { 0.5f * data->scale, 0, 0.5f * data->scale }); // half voxel addition
        float3 point_start = voxel_position;
        float3 point_end = float3_add(voxel_position, (float3) { 0, 1.0f, 0 });
        render_line3D(data->world, point_start, point_end, debug_color);
        /*for (byte i = 0; i < octree_length; i++) {
            if (data->chunk->nodes[i].nodes != NULL) return; // if a child node is open, then don't close this node
            const byte node_value = data->chunk->nodes[i].value;
            if (node_value) {
                float3 end_point = float3_add(position3D->value, (float3) { 0, ray_length, 0 });
                render_line3D(world, position3D->value, end_point, debug_color);
            }
        }*/
    }
}

void ChunkDebugSystem(ecs_iter_t *it) {
    if (!is_render_chunk_edges) {
        return;
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(RenderLod)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderLod, renderLod)
        if (renderLod->value != 0) {
            continue;
        }
        TraverseChunk data = (TraverseChunk) {
            .world = world,
            .scale = get_terrain_voxel_scale(nodeDepth->value),
            .chunk = voxelNode,
            .position = byte3_zero,
            .depth = 0,
            .target_depth = nodeDepth->value,
            .chunk_position = position3D->value
        };
        traverse_chunk(&data);
        /*float3 end_point = float3_add(position3D->value, (float3) { 0, ray_length, 0 });
        render_line3D(world, position3D->value, end_point, debug_color);*/
    }
} zox_declare_system(ChunkDebugSystem)