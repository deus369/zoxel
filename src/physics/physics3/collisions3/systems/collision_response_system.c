// uses last position to get new position
/*#define respond_collision(d)\
    if (did_collide_##d) {\
        velocity3D->value.d *= -bounce_lost_force; \
        float3 collision_point = position_last;\
        float offset_delta = did_collide_##d == 2 ? -collision_distance.d : collision_distance.d; \
        float voxel_point = position_new.d + offset_delta;\
        if (did_collide_##d == 1) {\
            voxel_point = floor(voxel_point / terrain_scale) * terrain_scale;\
        } else {\
            voxel_point = ceil(voxel_point / terrain_scale) * terrain_scale;\
        }\
        float penetration = offset_delta - voxel_point; \
        float delta = position_last.d + penetration;\
        position3D->value.d = position_last.d - delta;\
    }*/

const float penetration_amplifier = 1.0f; // 1.01f

#define respond_collision_pen(d)\
    if (did_collide_##d) {\
        byte negative = did_collide_##d == 2; \
        float penetration = negative ? -collision_distance.d : collision_distance.d; \
        position3D->value.d -= penetration * penetration_amplifier;\
        velocity3D->value.d *= -bounce_lost_force; \
    }

void CollisionResponseSystem(iter *it) {
    zox_sys_world();
    zox_sys_begin();
    zox_sys_in(VoxLink)
    zox_sys_in(CollisionDistance)
    zox_sys_out(Position3D)
    zox_sys_out(Velocity3D)
    zox_sys_out(LastPosition3D)
    zox_sys_out(Collision)
    zox_sys_out(Grounded)
    // now do collisions
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(VoxLink, voxLink)
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
        // zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        const float3 position_last = lastPosition3D->value;
        const float3 position_new = position3D->value;
        const float3 collision_distance = collisionDistance->value;
        // Unpacking:
        byte did_collide_x = (collision->value >> 0) & 0x3;
        byte did_collide_y = (collision->value >> 2) & 0x3;
        byte did_collide_z = (collision->value >> 4) & 0x3;
        const byte is_falling = velocity3D->value.y < 0;

        respond_collision_pen(x);
        respond_collision_pen(y);
        respond_collision_pen(z);

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

        // debugs
        /*zox_log("is_falling: %i", is_falling);
        zox_log("did_collide_y: %i", did_collide_y);
        zox_log("grounded: %i", grounded->value);*/
    }
} zoxd_system(CollisionResponseSystem)