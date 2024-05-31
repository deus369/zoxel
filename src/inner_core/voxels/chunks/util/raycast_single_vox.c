const float ray_interval_mini = 0.001f;

void raycast_terrain_gizmo_block_vox(ecs_world_t *world, const ecs_entity_t chunk, const float3 ray_origin, const float3 ray_normal, const float3 old_hit_normal) {
    if (!chunk) return;
    float model_scale = 64.0f; // 32 resolution by terrain is 0.5 so we get 64.
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (chunk_octree == NULL) return;
    const float3 block_position = zox_get_value(chunk, Position3D)
    // render_line3D(world, block_position, float3_add(block_position, float3_up), (color_rgb) { 0, 255, 0 });
    const int3 chunk_size = zox_get_value(chunk, ChunkSize)
    float3 real_size = float3_multiply_float(int3_to_float3(chunk_size), 1 / model_scale);
    int3 cache_position = (int3) { -666, -666, -666 };
    float3 hit_point = float3_zero;
    unsigned char ray_hit = 0;
    float3 hit_normal = float3_zero;
    for (float i = 0; i < 1.0f; i += ray_interval_mini) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        float3 local_point = float3_sub(point, block_position);
        float3_add_float3_p(&local_point, float3_multiply_float(real_size, 0.5f));
        int3 voxel_position = float3_to_int3(float3_multiply_float(local_point, model_scale));
        if (!int3_in_bounds(voxel_position, chunk_size)) continue;
        if (int3_equals(cache_position, voxel_position)) continue;
        byte3 temp = int3_to_byte3(voxel_position);
        const unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (old_voxel) {
            ray_hit = 1;
            hit_point = point;
            // if (cache_position.x == -666) zox_log("raycast hit from outside vox\n")
            if (cache_position.x == -666) hit_normal = old_hit_normal;
            else hit_normal = float3_from_int3(int3_sub(cache_position, voxel_position));
            break;
        }
        cache_position = voxel_position;
    }
    if (ray_hit) {
        // zox_log(" > ray hit at %fx%fx%f\n", hit_point.x, hit_point.y, hit_point.z)
        render_line3D(world, hit_point, float3_add(hit_point, float3_multiply_float(hit_normal, 1 / model_scale)), (color_rgb) { 0, 255, 0 });
    }
}

void raycast_block_vox(ecs_world_t *world, const ecs_entity_t chunk, const float3 ray_origin, const float3 ray_normal, const unsigned char voxel, const unsigned char hit_type) {
    if (!chunk) return;
    float model_scale = 64.0f; // 32 resolution by terrain is 0.5 so we get 64.
    const ChunkOctree *chunk_octree = zox_get(chunk, ChunkOctree)
    if (chunk_octree == NULL) return;
    const float3 block_position = zox_get_value(chunk, Position3D)
    const byte3 chunk_size = int3_to_byte3(zox_gett_value(chunk, ChunkSize));
    const float3 real_size = float3_multiply_float(byte3_to_float3(chunk_size), 1 / model_scale);
    byte3 cache_position = (byte3) { 255, 255, 255 };
    for (float i = 0; i < 1.0f; i += ray_interval_mini) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        float3 local_point = float3_sub(point, block_position);
        float3_add_float3_p(&local_point, float3_multiply_float(real_size, 0.5f));
        byte3 voxel_position = int3_to_byte3(float3_to_int3(float3_multiply_float(local_point, model_scale)));
        if (!byte3_in_bounds(voxel_position, chunk_size)) continue;
        if (byte3_equals(cache_position, voxel_position)) continue;
        byte3 temp = (voxel_position);
        const unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (old_voxel) {
            // zox_log(" placing on minivox block [%i]\n", old_voxel)
            if (hit_type == 2) cache_position = voxel_position;
            ChunkOctree *chunk_octree2 = zox_get_mut(chunk, ChunkOctree)
            const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
            SetVoxelData data = { .node = chunk_octree2, .position = cache_position };
            set_voxel(&datam, data);
            close_same_nodes(chunk_octree2);
            zox_modified(chunk, ChunkOctree)
            zox_set(chunk, ChunkDirty, { 1 })
            break;
        }
        cache_position = voxel_position;
    }
}
