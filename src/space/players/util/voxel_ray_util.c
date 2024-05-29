const float ray_interval = 0.05f;
const float ray_length = 16;

void draw_ray_voxel_point(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player) {
    // find point where intersects voxel
    if (!realm || !zox_has(realm, TerrainLink)) return;
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    if (!terrain) return;
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    if (!chunk_links) return;
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    if (!camera) return;
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    int3 cache_position = int3_zero;
    float3 hit_point = float3_zero;
    unsigned char ray_hit = 0;
    float3 hit_normal = float3_zero;
    for (float i = 0; i < ray_length; i += ray_interval) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        int3 chunk_position = real_position_to_chunk_position(point, default_chunk_size);
        // should do a check if chunk_position changed
        const ecs_entity_t chunk = int3_hash_map_get(chunk_links->value, chunk_position);
        if (!chunk) continue;
        ChunkOctree *chunk_octree = zox_get_mut(chunk, ChunkOctree)
        int3 voxel_position = real_position_to_voxel_position(point);
        if (int3_equals(cache_position, voxel_position)) continue;
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
        byte3 temp = voxel_position_local;
        const unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (old_voxel) {
            ray_hit = 1;
            hit_point = point;
            hit_normal = float3_from_int3(int3_sub(cache_position, voxel_position));
            break;
        }
        cache_position = voxel_position;
    }
    if (ray_hit) {
        // zox_log(" > ray hit at %fx%fx%f\n", hit_point.x, hit_point.y, hit_point.z)
        render_line3D(world, hit_point, float3_add(hit_point, float3_multiply_float(hit_normal, 0.5f)), (color_rgb) { 0, 0, 155 });
    }
}

void set_player_voxel_ray(ecs_world_t *world, const ecs_entity_t realm, const ecs_entity_t player, const unsigned char travel_voxel, const unsigned char voxel, unsigned char hit_only) {
    const ecs_entity_t terrain = zox_get_value(realm, TerrainLink)
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    const ecs_entity_t camera = zox_get_value(player, CameraLink)
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    int3 cache_position = int3_zero;
    byte3 cache_position_local = byte3_zero;
    ecs_entity_t cache_chunk = 0;
    for (float i = 0; i < ray_length; i += ray_interval) {
        float3 point = float3_add(ray_origin, float3_multiply_float(ray_normal, i));
        int3 chunk_position = real_position_to_chunk_position(point, default_chunk_size);
        // should do a check if chunk_position changed
        const ecs_entity_t chunk = int3_hash_map_get(chunk_links->value, chunk_position);
        if (!chunk) continue;
        if (!cache_chunk) cache_chunk = chunk;
        ChunkOctree *chunk_octree = zox_get_mut(chunk, ChunkOctree)
        int3 voxel_position = real_position_to_voxel_position(point);
        if (int3_equals(cache_position, voxel_position)) continue;
        cache_position = voxel_position;
        byte3 voxel_position_local = get_local_position_byte3(voxel_position, chunk_position, default_chunk_size_byte3);
        byte3 temp = voxel_position_local;
        unsigned char old_voxel = get_octree_voxel(chunk_octree, &temp, max_octree_depth);
        if (hit_only) {
            if (old_voxel) {
                if (hit_only == 2) {
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
                return;
            }
            cache_chunk = chunk;
            cache_position_local = voxel_position_local;
            continue;
        }
        if (travel_voxel != old_voxel) return;
        const SetVoxelTargetData datam = { .depth = max_octree_depth, .voxel = voxel, .effect_nodes = 1 };
        SetVoxelData data = { .node = chunk_octree, .position = voxel_position_local };
        set_voxel(&datam, data);
        close_same_nodes(chunk_octree);
        zox_modified(chunk, ChunkOctree)
        zox_set(chunk, ChunkDirty, { 1 })
        // set surrounding chunks dirt if on edge... this feels familiar lmao
    }
}
