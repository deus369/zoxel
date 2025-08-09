// responding
// draw line for collided voxels
extern ecs_entity_t spawn_line3D_colored(ecs*, const float3, const float3, float, double, const color_rgb);
const byte3 zox_debug_collision_response = (byte3) { 1, 1, 1 };
const double debug_collision_lifetime = 30;
const double debug_collision_line_length = 0.5;

// uses last position to get new position
#define debug_collision_d(d, c1, c2)\
if (did_collide##_##d) {\
    float3 collision_point = pointf_last;\
    float offset_delta = did_collide_##d == 2 ? -collision_distance.d : collision_distance.d; \
    collision_point.d = pointf_new.d + offset_delta;\
    \
    float voxel_point;\
    if (did_collide_##d == 1) {\
        voxel_point = floor(collision_point.d / terrain_scale) * terrain_scale;\
    } else {\
        voxel_point = ceil(collision_point.d / terrain_scale) * terrain_scale;\
    }\
    \
    if (zox_debug_collision_response.d) {\
        \
        /*zox_log("hit dim [%s] p[%f] v[%f] direction [%i]", #d, pointf_last.y, voxel_point, did_collide_##d); */\
        \
        float3 voxel_normal = float3_zero;\
        color_rgb c = c1; \
        voxel_normal.d = 1;\
        if (did_collide_##d == 1) {\
            voxel_normal.d *= -1;\
            c = c2; \
        }\
        spawn_line3D_colored( \
            world, \
            collision_point, \
            float3_add(collision_point, float3_scale(voxel_normal, debug_collision_line_length)), \
            2, \
            debug_collision_lifetime, \
            c);\
    }\
}


#define debug_collision_d_pen(d, negative_color, positive_color)\
if (did_collide##_##d) {\
    float3 hit = pointf_new;\
    float3 hit_pen = pointf_new;\
    byte negative = did_collide_##d == 2; \
    float penetration = negative ? -collision_distance.d : collision_distance.d; \
    float bounds_delta = negative ? -bounds->value.d : bounds->value.d; \
    hit.d += bounds_delta;\
    hit_pen.d += bounds_delta + penetration;\
    \
    if (zox_debug_collision_response.d) {\
        \
        color_rgb c = negative ? negative_color : positive_color; \
        float3 normal = float3_zero;\
        normal.d = negative ? 1 : -1;\
        \
        spawn_line3D_colored( \
            world, \
            hit_pen, \
            hit, \
            2, \
            debug_collision_lifetime, \
            color_rgb_black);\
        \
        spawn_line3D_colored( \
            world, \
            hit, \
            float3_add(hit, float3_scale(normal, debug_collision_line_length)), \
            2, \
            debug_collision_lifetime, \
            c);\
    }\
}


void CollisionDebugSystem(iter *it) {
    if (!is_debug_collisions) {
        return;
    }
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(VoxLink);
    zox_sys_in(CollisionDistance);
    zox_sys_in(Position3D);
    zox_sys_in(LastPosition3D);
    zox_sys_in(Collision);
    zox_sys_in(Bounds3D);
    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink);
        zox_sys_i(CollisionDistance, collisionDistance);
        zox_sys_i(Position3D, position);
        zox_sys_i(LastPosition3D, lastPosition3D);
        zox_sys_i(Collision, collision);
        zox_sys_i(Bounds3D, bounds);
        if (!collision->value) {
            continue;
        }
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        // const float3 pointf_last = lastPosition3D->value;
        const float3 pointf_new = position->value;
        const float3 collision_distance = collisionDistance->value;
        // Unpacking:
        byte did_collide_x = (collision->value >> 0) & 0x3;
        byte did_collide_y = (collision->value >> 2) & 0x3;
        byte did_collide_z = (collision->value >> 4) & 0x3;
        // const byte is_falling = velocity3D->value.y < 0;
        debug_collision_d_pen(y, color_rgb_green, color_rgb_yellow);
        debug_collision_d_pen(x, color_rgb_blue, color_rgb_cyan);
        debug_collision_d_pen(z, color_rgb_red, color_rgb_purple);
    }
} zoxd_system(CollisionDebugSystem)