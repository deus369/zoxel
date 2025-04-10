// using DDA for raycasting
void raycast_terrain_gizmo(ecs_world_t *world, const ecs_entity_t caster, const ecs_entity_t camera, const ecs_entity_t terrain, RaycastVoxelData *data) {
    if (!zox_valid(terrain) || !zox_has(terrain, RealmLink) || !zox_valid(camera) || !zox_has(camera, RaycastOrigin)) {
        return;
    }
    const ecs_entity_t realm = zox_get_value(terrain, RealmLink)
    const VoxelLinks *voxels = zox_get(realm, VoxelLinks)
    const ChunkLinks *chunk_links = zox_get(terrain, ChunkLinks)
    const float3 ray_origin = zox_get_value(camera, RaycastOrigin)
    const float3 ray_normal = zox_get_value(camera, RaycastNormal)
    int3 chunk_position = (int3) { 255255, 255255, 255255 };
    byte ray_hit = raycast_general(world, caster, voxels, chunk_links, chunk_position, float3_zero, default_chunk_size, 0, ray_origin, ray_normal, 0.5f, terrain_ray_length, data);
    if (ray_hit == ray_hit_type_terrain) {
        float3 voxel_position_real = data->position_real;
        float3 center_quad = float3_add(voxel_position_real, float3_multiply_float(int3_to_float3(data->normal), data->voxel_scale * 0.501f));
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
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, other_axis.y, other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { -other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, -other_axis.y, -other_axis.z }),
                raycast_quad_color, raycast_thickness);
        } else {
            // handles x and y
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, -other_axis.z }),
                float3_add(center_quad, (float3) { -other_axis.x, -other_axis.y, -other_axis.z }),
                raycast_quad_color, raycast_thickness);
            render_line3D_thickness(world,
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, other_axis.z }),
                float3_add(center_quad, (float3) { other_axis.x, other_axis.y, -other_axis.z }),
                raycast_quad_color, raycast_thickness);
        }
        // zox_log(" > h [%fx%fx%f]\n", data->hit.x, data->hit.y, data->hit.z)
        // zox_log(" > r [%fx%fx%f]\n", data->position_real.x, data->position_real.y, data->position_real.z)
    } else if (ray_hit == ray_hit_type_character) {
        // zox_log("raycast hit character!\n")
        const color_rgb hit_point_line_color = (color_rgb) { 55, 45, 45 };
        render_line3D(world, data->hit, float3_add(data->hit, float3_multiply_float(float3_up, 0.3f)), hit_point_line_color);
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
        raycast_terrain_gizmo(world, e, cameraLink->value, voxLink->value, raycastVoxelData);
    }
} zox_declare_system(RaycastGizmoSystem)
