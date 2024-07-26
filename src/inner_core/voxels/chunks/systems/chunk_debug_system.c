// show lines on quads along chunk edge
unsigned char is_render_chunk_edges = 0;

extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

// todo: traverse chunk ChunkOctree
// todo: using neighbor voxels, perform a function at target depth
// todo: pass data in function

typedef struct {
    ecs_world_t *world;
    const ChunkOctree *chunk;
    byte3 position;
    unsigned char depth;
    const unsigned char target_depth;
    const float3 chunk_position;
} TraverseChunk;

void traverse_chunk(TraverseChunk *data) {
    if (!data->chunk) return;
    if (data->depth != data->target_depth) {
        if (!data->chunk->nodes) return; // if node is closed
        const unsigned char depth = data->depth + 1;
        // const unsigned char dividor = powers_of_two_byte[depth - 1];
        const ChunkOctree *chunk = data->chunk;
        byte3 position_parent = data->position;
        byte3_multiply_byte(&position_parent, 2);
        for (unsigned char i = 0; i < octree_length; i++) {
            data->chunk = &chunk->nodes[i];
            data->depth = depth;
            data->position = byte3_add(position_parent, octree_positions_b[i]);
            traverse_chunk(data);
        }
    } else {
        // only for edge voxels
        if (!byte3_on_edge_xz(data->position, (byte3) { 32, 32, 32 })) return;
        const color_rgb debug_color = { 255, 0, 0 };
        // zox_log(" > depth [%i] line at position: %ix%ix%i\n", data->depth, data->position.x, data->position.y, data->position.z)
        float3 voxel_position = float3_add(data->chunk_position, (float3) { data->position.x / 2.0f, data->position.y / 2.0f, data->position.z / 2.0f });
        float3_add_float3_p(&voxel_position, (float3) { 0.25f, 0, 0.25f }); // half voxel addition
        float3 point_start = voxel_position;
        float3 point_end = float3_add(voxel_position, (float3) { 0, 1.0f, 0 });
        render_line3D(world, point_start, point_end, debug_color);
        /*for (unsigned char i = 0; i < octree_length; i++) {
            if (data->chunk->nodes[i].nodes != NULL) return; // if a child node is open, then don't close this node
            const unsigned char node_value = data->chunk->nodes[i].value;
            if (node_value) {
                float3 end_point = float3_add(position3D->value, (float3) { 0, ray_length, 0 });
                render_line3D(world, position3D->value, end_point, debug_color);
            }
        }*/
    }
}

void ChunkDebugSystem(ecs_iter_t *it) {
    if (!is_render_chunk_edges) return;
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(ChunkOctree, chunkOctrees, 2)
    zox_field_in(RenderLod, renderLods, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderLod, renderLods, renderLod)
        if (renderLod->value > 1) continue;
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
        TraverseChunk data = (TraverseChunk) {
            .world = world,
            .chunk = chunkOctree,
            .position = byte3_zero,
            .depth = 0,
            .target_depth = max_octree_depth,
            .chunk_position = position3D->value
        };
        traverse_chunk(&data);
        /*float3 end_point = float3_add(position3D->value, (float3) { 0, ray_length, 0 });
        render_line3D(world, position3D->value, end_point, debug_color);*/
    }
} zox_declare_system(ChunkDebugSystem)
