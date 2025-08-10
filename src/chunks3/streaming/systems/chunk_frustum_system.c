// NOTE: uses zox_set here for children setting
// NOTE: I may need to thread lock/unlock ChunkEntities when reading
// block spawn delve function
void set_chunk_block_spawns_render_disabled(
    ecs *world,
    const VoxelNode *node,
    const byte state
) {
    if (is_closed_VoxelNode(node)) {
        return;
    } else if (is_linked_VoxelNode(node)) {
        const entity e = get_entity_VoxelNode(node);
        if (zox_valid(e)) {
            zox_set(e, RenderDisabled, { state })
        }
    } else if (has_children_VoxelNode(node)) {
        VoxelNode* kids = get_children_VoxelNode(node);
        for (int i = 0; i < octree_length; i++) {
            set_chunk_block_spawns_render_disabled(world, &kids[i], state);
        }
    }
}

void set_entity_render_disabled(ecs* world, entity e, byte disabled) {
    if (!zox_valid(e)) {
        return;
    }
    zox_set(e, RenderDisabled, { disabled })
    if (zox_has(e, ElementLinks)) {
        zox_geter(e, ElementLinks, elements);
        for (int k = 0; k < elements->length; k++) {
            const entity e2 = elements->value[k];
            if (!zox_valid(e2)) {
                continue;
            }
            if (zox_has(e2, RenderDisabled)) {
                zox_set(e2, RenderDisabled, { disabled });
            }
            set_entity_render_disabled(world, e2, disabled);
        }
    }
    if (zox_has(e, Children)) {
        zox_geter(e, Children, children);
        for (int l = 0; l < children->length; l++) {
            const entity e2 = children->value[l];
            if (!zox_valid(e2)) {
                continue;
            }
            if (zox_has(e2, RenderDisabled)) {
                zox_set(e2, RenderDisabled, { disabled });
            }
            set_entity_render_disabled(world, e2, disabled);
        }
    }
}

byte is_sphere_in_frustum(const plane* planes, float3 center, float radius) {
    for (int i = 0; i < 6; i++) {
        float dist = float3_dot(planes[i].normal, center) - planes[i].distance;
        if (dist < -radius) {
            return 0; // sphere is completely outside
        }
    }
    return 1;
}

// Fast AABB cull using positive-vertex trick (drop-in replacement)
byte aabb_in_frustum_fast(const plane *planes, const bounds b, float eps) {
    for (int i = 0; i < 6; ++i) {
        const plane p = planes[i];
        // choose farthest vertex in direction of plane normal
        float3 pv = {
            b.center.x + (p.normal.x >= 0.0f ? b.extents.x : -b.extents.x),
            b.center.y + (p.normal.y >= 0.0f ? b.extents.y : -b.extents.y),
            b.center.z + (p.normal.z >= 0.0f ? b.extents.z : -b.extents.z)
        };
        if (float3_dot(p.normal, pv) - p.distance > eps) return 0; // outside
    }
    return 1; // intersects/inside
}

// this sets RenderDisabled for chunks and their children
void ChunkFrustumSystem(iter *it) {
    const byte frustum_inwards = 1; // we just using this for safety
    zox_sys_query();
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(Position3D);
    zox_sys_in(Bounds3D);
    zox_sys_in(VoxScale);
    zox_sys_in(ChunkEntities);
    zox_sys_in(VoxelNode);
    zox_sys_out(RenderDisabled);
    for (int i = 0; i < it->count; i++) {
        zox_sys_e();
        zox_sys_i(Position3D, position);
        zox_sys_i(Bounds3D, bounds3);
        zox_sys_i(VoxScale, voxScale);
        zox_sys_i(ChunkEntities, entities);
        zox_sys_i(VoxelNode, voxelNode);
        zox_sys_o(RenderDisabled, renderDisabled);
        // our bounds3D isn't centred, terrain chunks corner offset!
        bounds chunk_bounds = {
            .center = float3_add(position->value, bounds3->value),
            .extents = bounds3->value
        };
        float3_scale_p(&chunk_bounds.extents, fudge_frustum_extents);
        zox_sys_query_begin();
        byte is_viewed = disable_frustum_culling;
        while (zox_sys_query_loop()) {
            if (is_viewed) {
                continue;   // make sure to iterate all flecs query
            }
            zox_sys_begin_2();
            zox_sys_in_2(Position3DBounds);
            zox_sys_in_2(CameraPlanes);
            for (int j = 0; j < it2.count; j++) {
                zox_sys_i_2(Position3DBounds, frustum_bounds);
                zox_sys_i_2(CameraPlanes, planes);
                // our normals appear to be flipped
                byte inside_sphere = is_sphere_in_frustum(
                    planes->value,
                    chunk_bounds.center,
                    float3_length(chunk_bounds.extents));
                is_viewed = inside_sphere &&
                        is_bounds_in_position_bounds(frustum_bounds->value, chunk_bounds) &&
                        is_in_frustum(planes->value, chunk_bounds, frustum_inwards);
                if (is_viewed) {
                    break;
                }
            }
        }
        zox_sys_query_end();
        if (renderDisabled->value != !is_viewed) {
            renderDisabled->value = !is_viewed;
            // -=- Block Spawns -=-
            if (zox_gett_value(e, BlocksSpawned)) {
                set_chunk_block_spawns_render_disabled(
                    world,
                    voxelNode,
                    renderDisabled->value);
            }
            // -=- -=- -=- -=- -=- -=-
            for (int j = 0; j < entities->length; j++) {
                const entity e2 = entities->value[j];
                set_entity_render_disabled(
                    world,
                    e2,
                    renderDisabled->value);
            }
            // -=- -=- -=- -=- -=- -=-
        }
    }
} zoxd_system(ChunkFrustumSystem)