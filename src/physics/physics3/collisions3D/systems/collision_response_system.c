// responding
// draw line for collided voxels
extern void render_line3D(ecs_world_t *world, const float3 a, const float3 b, const color_rgb line_color);

// uses last position to get new position
#define respond_collision(d)\
    if (did_collide##_##d) {\
        /*float delta_time_adjustment = 1.0f / (60 * delta_time);*/\
        velocity3D->value.d *= -bounce_lost_force; /* * pow(bounce_dampening, delta_time);*/\
        float3 collision_point = position_last;\
        collision_point.d = position_new.d + collision_distance.d;\
        /* convert real position to voxel one */\
        float voxel_point;\
        if (did_collide##_##d == 1) {\
            voxel_point = floor(collision_point.d * get_terrain_voxel_scale_inverse(max_depth)) / get_terrain_voxel_scale_inverse(max_depth);\
        } else {\
            voxel_point = ceil(collision_point.d * get_terrain_voxel_scale_inverse(max_depth)) / get_terrain_voxel_scale_inverse(max_depth);\
        }\
        /* convert real position to voxel one */\
        float delta = (position_last.d + collision_distance.d) - voxel_point;\
        position3D->value.d = position_last.d - delta;\
        if (zox_debug_collision_response.d) {\
            float3 voxel_normal = float3_zero;\
            voxel_normal.d = 1;\
            if (did_collide##_##d == 1) {\
                voxel_normal.d *= -1;\
            }\
            render_line3D(world, collision_point, float3_add(collision_point, voxel_normal), color_rgb_white);\
        }\
    }

#define respond_to_collisions()\
    respond_collision(x)\
    respond_collision(y)\
    respond_collision(z)


void CollisionResponseSystem(ecs_iter_t *it) {
    const byte max_depth = terrain_depth;   // todo: use chunk max depths here
    zox_sys_world()
    zox_sys_begin()
    //zox_sys_in(VoxLink)
    // zox_sys_in(Bounds3D)
    zox_sys_in(CollisionDistance)
    zox_sys_out(Position3D)
    zox_sys_out(Velocity3D)
    zox_sys_out(LastPosition3D)
    zox_sys_out(Collision)
    zox_sys_out(Grounded)
    // now do collisions
    for (int i = 0; i < it->count; i++) {
        //zox_sys_i(VoxLink, voxLink)
        // zox_sys_i(Bounds3D, bounds3D)
        zox_sys_i(CollisionDistance, collisionDistance)
        zox_sys_o(Position3D, position3D)
        zox_sys_o(Velocity3D, velocity3D)
        zox_sys_o(LastPosition3D, lastPosition3D)
        zox_sys_o(Collision, collision)
        zox_sys_o(Grounded, grounded)
        if (!collision->value) {
            grounded->value = 0;
            lastPosition3D->value = position3D->value;
            continue;
        }
        const float3 position_last = lastPosition3D->value;
        const float3 position_new = position3D->value;
        const float3 collision_distance = collisionDistance->value;
        // Unpacking:
        byte did_collide_x = (collision->value >> 0) & 0x3;
        byte did_collide_y = (collision->value >> 2) & 0x3;
        byte did_collide_z = (collision->value >> 4) & 0x3;
        const byte is_falling = velocity3D->value.y < 0;
        respond_to_collisions()
        // keeps grounded for an additional frame
        if (did_collide_y && is_falling) {
            grounded->value = 1;
        } else {
            if (grounded->value == 1) {
                grounded->value = 2;
            } else {
                grounded->value = 0;
            }
        }
        lastPosition3D->value = position3D->value;
        collision->value = 0;
        // zox_log("grounded: %i", grounded->value)
    }
} zox_declare_system(CollisionResponseSystem)