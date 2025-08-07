// responding
// draw line for collided voxels
extern void render_line3D(ecs *world, const float3 a, const float3 b, const color_rgb line_color);
const byte3 zox_debug_collision_response = (byte3) { 1, 1, 1 };

// uses last position to get new position
#define debug_collision_d(d, c1, c2)\
if (did_collide##_##d) {\
    float3 collision_point = position_last;\
    collision_point.d = position_new.d + collision_distance.d;\
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
        zox_log("hit dim [%s] p[%f] v[%f] direction [%i]", #d, position_last.y, voxel_point, did_collide_##d); \
        \
        float3 voxel_normal = float3_zero;\
        color_rgb c = c1; \
        voxel_normal.d = 1;\
        if (did_collide_##d == 1) {\
            voxel_normal.d *= -1;\
            c = c2; \
        }\
        render_line3D(world, collision_point, float3_add(collision_point, voxel_normal), c);\
    }\
}


void CollisionDebugSystem(iter *it) {
    if (!is_debug_collisions) {
        return;
    }
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(VoxLink)
    zox_sys_in(CollisionDistance)
    zox_sys_in(Position3D)
    // zox_sys_in(Velocity3D)
    zox_sys_in(LastPosition3D)
    zox_sys_in(Collision)
    // zox_sys_in(Grounded)
    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(CollisionDistance, collisionDistance)
        zox_sys_i(Position3D, position3D)
        // zox_sys_i(Velocity3D, velocity3D)
        zox_sys_i(LastPosition3D, lastPosition3D)
        zox_sys_i(Collision, collision)
        // zox_sys_i(Grounded, grounded)
        if (!collision->value) {
            continue;
        }
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        const float3 position_last = lastPosition3D->value;
        const float3 position_new = position3D->value;
        const float3 collision_distance = collisionDistance->value;
        // Unpacking:
        byte did_collide_x = (collision->value >> 0) & 0x3;
        byte did_collide_y = (collision->value >> 2) & 0x3;
        byte did_collide_z = (collision->value >> 4) & 0x3;
        // const byte is_falling = velocity3D->value.y < 0;
        debug_collision_d(x, color_rgb_blue, color_rgb_green);
        debug_collision_d(z, color_rgb_cyan, color_rgb_purple);
        debug_collision_d(y, color_rgb_white, color_rgb_red);
    }
} zox_declare_system(CollisionDebugSystem)