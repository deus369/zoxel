const float ray_interval = 0.04f;
const float ray_length = 6;

/*zox_log(" > point [%fx%fx%f]\n", point.x, point.y, point.z)
zox_log(" > block_position [%fx%fx%f]\n", block_position.x, block_position.y, block_position.z)
zox_log(" > local_point [%fx%fx%f]\n", local_point.x, local_point.y, local_point.z)
zox_log(" + voxel_position [%ix%ix%i]\n", voxel_position.x, voxel_position.y, voxel_position.z)*/

void raycast_terrain_gizmo(ecs_world_t *world, const ecs_entity_t camera, const ecs_entity_t terrain) {
    if (!terrain || !camera || !zox_has(camera, RaycastOrigin)) return;
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    int3 cache_position = int3_zero;
    float3 hit_point = float3_zero;
    unsigned char ray_hit = 0;
    float3 hit_normal = float3_zero;
    float3 cache_point = float3_zero;
    int3 cached_chunk_position = (int3) { 255255, 255255, 255255 };
    ecs_entity_t chunk;
    const ChunkOctree *chunk_octree;
    for (float i = 0; i < ray_length; i += ray_interval) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        int3 chunk_position = real_position_to_chunk_position(point, default_chunk_size);
        if (!int3_equals(cached_chunk_position, chunk_position)) {
            chunk = int3_hashmap_get(chunk_links->value, chunk_position);
            if (!chunk) return;
            chunk_octree = zox_get(chunk, ChunkOctree)
            if (!chunk_octree) return;
            cached_chunk_position = chunk_position;
        }
        // should do a check if chunk_position changed
        int3 voxel_position = real_position_to_voxel_position(point);
        if (int3_equals(cache_position, voxel_position)) continue;
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
        byte3 temp = voxel_position_local;
        const unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (old_voxel) {
            // move into minivox
            hit_normal = float3_from_int3(int3_sub(cache_position, voxel_position));
            unsigned char selected_mini = 0;
            if (is_select_minis) {
                const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
                const ecs_entity_t block = voxels->value[old_voxel - 1];
                if (zox_has(block, BlockVox)) {
                    const BlockSpawns *spawns = zox_get(chunk, BlockSpawns)
                    if (spawns->value && spawns->value->data) {
                        const ecs_entity_t block_spawn = byte3_hashmap_get(spawns->value, voxel_position_local);
                        raycast_terrain_gizmo_block_vox(world, block_spawn, cache_point, ray_normal, hit_normal);
                        selected_mini = 1;
                    }
                }
            }
            if (!selected_mini){
                ray_hit = 1;
                hit_point = point;
            }
            break;
        }
        cache_position = voxel_position;
        cache_point = point;
    }
    if (ray_hit) {
        // zox_log(" > ray hit at %fx%fx%f\n", hit_point.x, hit_point.y, hit_point.z)
        render_line3D(world, hit_point, float3_add(hit_point, float3_multiply_float(hit_normal, 0.5f)), (color_rgb) { 0, 0, 155 });
    }
}

void raycast_terrain(ecs_world_t *world, const ecs_entity_t camera, const ecs_entity_t terrain, const unsigned char travel_voxel, const unsigned char voxel, unsigned char hit_type) {
    if (!terrain) return;
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    int3 cache_position = int3_zero;
    byte3 cache_position_local = byte3_zero;
    float3 cache_point = float3_zero;
    ecs_entity_t cache_chunk = 0;
    for (float i = 0; i < ray_length; i += ray_interval) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        int3 chunk_position = real_position_to_chunk_position(point, default_chunk_size);
        // should do a check if chunk_position changed
        const ecs_entity_t chunk = int3_hashmap_get(chunk_links->value, chunk_position);
        if (!chunk) continue;
        if (!cache_chunk) cache_chunk = chunk;
        ChunkOctree *chunk_octree = zox_get_mut(chunk, ChunkOctree)
        if (!chunk_octree) return;
        int3 voxel_position = real_position_to_voxel_position(point);
        if (int3_equals(cache_position, voxel_position)) continue;
        cache_position = voxel_position;
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
        byte3 temp = voxel_position_local;
        unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (hit_type) {
            if (old_voxel) {
                unsigned char selected_mini = 0;
                // move into minivox
                if (is_select_minis) {
                    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
                    const ecs_entity_t block = voxels->value[old_voxel - 1];
                    if (zox_has(block, BlockVox)) {
                        const BlockSpawns *spawns = zox_get(chunk, BlockSpawns)
                        if (spawns->value && spawns->value->data) {
                            const ecs_entity_t block_spawn = byte3_hashmap_get(spawns->value, voxel_position_local);
                            raycast_block_vox(world, block_spawn, cache_point, ray_normal, voxel, hit_type);
                            selected_mini = 1;
                        }
                    }
                }
                if (!selected_mini) {
                    if (hit_type == 2) {
                        cache_chunk = chunk;
                        cache_position_local = voxel_position_local;
                    }
                    ChunkOctree *chunk_octree2 = zox_get_mut(cache_chunk, ChunkOctree)
                    const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
                    SetVoxelData data = { .node = chunk_octree2, .position = cache_position_local };
                    set_voxel(&datam, data);
                    close_same_nodes(chunk_octree2);
                    zox_modified(cache_chunk, ChunkOctree)
                    zox_set(cache_chunk, ChunkDirty, { 1 })
                    if (byte3_on_edge(cache_position_local, default_chunk_size_byte3)) {
                        const ChunkNeighbors *chunk_neighbors = zox_get(cache_chunk, ChunkNeighbors)
                        for (int axis = 0; axis < 6; axis++) {
                            if (byte3_on_edge_axis(cache_position_local, default_chunk_size_byte3, axis)) {
                                zox_set(chunk_neighbors->value[axis], ChunkDirty, { 1 })
                            }
                        }
                    }
                }
                break;
            }
            cache_chunk = chunk;
            cache_position_local = voxel_position_local;
            cache_point = point;
        } else {
            if (travel_voxel != old_voxel) break;
            const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
            SetVoxelData data = { .node = chunk_octree, .position = voxel_position_local };
            set_voxel(&datam, data);
            close_same_nodes(chunk_octree);
            zox_modified(chunk, ChunkOctree)
            zox_set(chunk, ChunkDirty, { 1 })
            // set surrounding chunks dirt if on edge... this feels familiar lmao
        }
    }
}
