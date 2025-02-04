// responding
// draw line for collided voxels
extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

// positions from new position - uses collision point to reverse
#define respond_collision_reverse(d)\
if (did_collide##_##d) {\
    velocity3D->value.d *= -bounce_lost_force;\
    float3 voxel_normal = float3_zero;\
    voxel_normal.d = 1;\
    if (did_collide##_##d == 1) voxel_normal.d *= -1;\
    float3 collision_point = position_last;\
    collision_point.d = position_new.d + collision_offset.d;\
    /* convert real position to voxel one */\
    float voxel_point = 0;\
    if (did_collide##_##d == 1) voxel_point = floor(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
    else voxel_point = ceil(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
    /* convert real position to voxel one */\
    float delta = collision_point.d - voxel_point;\
    position3D->value.d = position_new.d - delta;\
    if (zox_debug_collision_response.d) render_line3D(world, collision_point, float3_add(collision_point, voxel_normal), color_rgb_white);\
    /*if (is_log) zox_log(" + at [%f] bob [%f] voxel [%f] delta distance [%f] normal [%f]\n", zox_current_time, collision_point.d, voxel_point, delta, voxel_normal.d)*/\
}

// uses last position to get new position
#define respond_collision(d)\
if (did_collide##_##d) {\
    /*float delta_time_adjustment = 1.0f / (60 * delta_time);*/\
    velocity3D->value.d *= -bounce_lost_force; /* * pow(bounce_dampening, delta_time);*/\
    float3 collision_point = position_last;\
    collision_point.d = position_new.d + collision_offset.d;\
    /* convert real position to voxel one */\
    float voxel_point;\
    if (did_collide##_##d == 1) voxel_point = floor(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
    else voxel_point = ceil(collision_point.d * terrain_voxel_scale_inverse) / terrain_voxel_scale_inverse;\
    /* convert real position to voxel one */\
    float delta = (position_last.d + collision_offset.d) - voxel_point;\
    position3D->value.d = position_last.d - delta;\
    if (zox_debug_collision_response.d) {\
        float3 voxel_normal = float3_zero;\
        voxel_normal.d = 1;\
        if (did_collide##_##d == 1) voxel_normal.d *= -1;\
        render_line3D(world, collision_point, float3_add(collision_point, voxel_normal), color_rgb_white);\
    }\
}

#define respond_to_collisions()\
respond_collision(x)\
respond_collision(y)\
respond_collision(z)
