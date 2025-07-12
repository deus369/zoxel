// using DDA for raycasting
void raycast_terrain_gizmo(ecs_world_t *world,
    const ecs_entity_t caster,
    const ecs_entity_t camera,
    const ecs_entity_t terrain,
    RaycastVoxelData *data)
{
    if (!zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_valid(camera) || !zox_has(camera, RaycastOrigin)) {
        return;
    }
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    zox_geter(realm, VoxelLinks, voxels)
    zox_geter(terrain, ChunkLinks, chunk_links)
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    int3 chunk_position = (int3) { 255255, 255255, 255255 };
    byte ray_hit = raycast_general(world,
        caster,
        voxels,
        chunk_links,
        chunk_position,
        float3_zero,
        chunk_dimensions,
        0,
        ray_origin,
        ray_normal,
        get_terrain_voxel_scale(depth),
        terrain_ray_length,
        data);
    if (ray_hit == ray_hit_type_terrain) {
        float3 voxel_position_real = data->position_real;
        float3 center_quad = float3_add(voxel_position_real, float3_multiply_float(int3_to_float3(data->normal), data->voxel_scale * (0.501f)));
        float3 other_axis = float3_zero;
        if (data->normal.y != 0) {
            other_axis.x = 1;
            other_axis.z = 1;
        } else if (data->normal.x != 0) {
            other_axis.y = 1;
            other_axis.z = 1;
        } else if (data->normal.z != 0) {
            other_axis.x = 1;
            other_axis.y = 1;
        }
        other_axis = float3_multiply_float(other_axis, data->voxel_scale * 0.5f - data->voxel_scale * (0.125f / raycast_thickness));
        if (data->normal.z != 0) {
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, other_axis.y, other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { -other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, -other_axis.y, -other_axis.z }),
                hit_terrain_color, raycast_thickness);
        } else {
            // handles x and y
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                hit_terrain_color, raycast_thickness);
            render_line3D_thickness_alpha(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, -other_axis.z }),
                hit_terrain_color, raycast_thickness);
        }
        // zox_log(" > h [%fx%fx%f]\n", data->hit.x, data->hit.y, data->hit.z)
        // zox_log(" > r [%fx%fx%f]\n", data->position_real.x, data->position_real.y, data->position_real.z)
    } else if (ray_hit == ray_hit_type_character) {
        render_line3D_thickness_alpha(world, data->hit, float3_add(data->hit, float3_multiply_float(float3_up, 0.06f)), hit_character_color, raycast_thickness);
    } else if (ray_hit == ray_hit_type_block_vox) {
        render_line3D_thickness_alpha(world, data->hit, float3_add(data->hit, float3_multiply_float(int3_to_float3(data->normal), 0.03f)), hit_block_vox_color, raycast_thickness);
    }
}

void RaycastGizmoSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(CameraLink, cameraLinks, 1)
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(RaycastVoxelData, raycastVoxelDatas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(CameraLink, cameraLinks, cameraLink)
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_o(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        if (!zox_valid(cameraLink->value) || !zox_valid(voxLink->value)) {
            continue;
        }
        if (!zox_has(cameraLink->value, CharacterLink)) {
            zox_log_error("camera attached has no character link")
            continue;
        }
        // caster only valid if camera is attached
        // zox_geter_value(cameraLink->value, CanRoam, const byte, is_camera_free)
        zox_geter_value(cameraLink->value, CharacterLink, const ecs_entity_t, e2)
        ecs_entity_t caster = e2 == e ? e : 0;
        raycast_terrain_gizmo(world,
            caster,
            cameraLink->value,
            voxLink->value,
            raycastVoxelData);
    }
} zox_declare_system(RaycastGizmoSystem)