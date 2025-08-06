void Chunk3RaycastSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CameraLink)
    zox_sys_in(VoxLink)
    zox_sys_in(RaycastRange)
    zox_sys_out(RaycastVoxelData)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(CameraLink, cameraLink)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(RaycastRange, raycastRange)
        zox_sys_o(RaycastVoxelData, data)
        ecs_entity_t terrain = voxLink->value;
        ecs_entity_t camera = cameraLink->value;
        if (!zox_valid(camera) || !zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_has(camera, RaycastOrigin)) {
            continue;
        }
        if (!zox_has(camera, CharacterLink)) {
            zox_log_error("camera attached has no character link")
            continue;
        }
        zox_geter_value(camera, CharacterLink, ecs_entity_t, e2)
        ecs_entity_t caster = e2 == e ? e : 0;
        /*raycastVoxelData->result = raycast_terrain_gizmo(world,
                    caster,
                    cameraLink->value,
                    voxLink->value,
                    raycastVoxelData,
                    raycastRange->value);*/
        // TODO: Get Depth off terrain
        const byte depth = terrain_depth;
        const int3 chunk_dimensions = int3_single(powers_of_two[depth]);

        zox_geter_value(terrain, RealmLink, ecs_entity_t, realm);
        zox_geter(realm, VoxelLinks, voxels);
        zox_geter(terrain, ChunkLinks, chunk_links);
        zox_geter_value(camera, RaycastOrigin, float3, ray_origin);
        zox_geter_value(camera, RaycastNormal, float3, ray_normal);

        CharacterRaycast character_raycast = { };
        data->result = raycast_voxel_node(world,
            caster,
            voxels,
            chunk_links,
            (int3) { 255255, 255255, 255255 },
            float3_zero,
            chunk_dimensions,
            0,
            ray_origin,
            ray_normal,
            get_terrain_voxel_scale(depth),
            raycastRange->value,
            data,
            character_raycast);
    }
} zox_declare_system(Chunk3RaycastSystem)