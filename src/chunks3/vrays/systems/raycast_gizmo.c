color hit_terrain_color = (color) { 2, 145, 145, 55 };
color hit_character_color = (color) { 155, 45, 45, 65 };
color hit_block_vox_color = (color) { 55, 185, 145, 45 };

extern ecs_entity_t local_crosshair;
extern void crosshair_set_type(ecs_world_t*, ecs_entity_t, byte);

// using DDA for raycasting
byte create_raycast_gizmo(
    ecs_world_t *world,
    const RaycastVoxelData *data
) {
    byte ray_hit = data->result;
    if (ray_hit == ray_hit_type_terrain) {
        float3 voxel_position_real = data->position_real;
        float3 center_quad = float3_add(voxel_position_real, float3_scale(data->normal, data->voxel_scale * (0.501f)));
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
        other_axis = float3_scale(other_axis, data->voxel_scale * 0.5f - data->voxel_scale * (0.125f / raycast_thickness));
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
        // draw a cube above its head instead
        float3 b = float3_add(data->hit, float3_scale(float3_up, 0.06f));
        render_line3D_thickness_alpha(world, data->hit, b, hit_character_color, raycast_thickness);
    } else if (ray_hit == ray_hit_type_block_vox) {
        float3 b = float3_add(data->hit, float3_scale(data->normal, 0.03f));
        render_line3D_thickness_alpha(world, data->hit, b, hit_block_vox_color, raycast_thickness);
    }
    return ray_hit;
}

void RaycastGizmoSystem(ecs_iter_t *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(RaycastVoxelData);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RaycastVoxelData, data);
        crosshair_set_type(world, local_crosshair, data->result);
        create_raycast_gizmo(world, data);
    }
} zox_declare_system(RaycastGizmoSystem)