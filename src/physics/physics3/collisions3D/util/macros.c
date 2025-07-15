#define handle_collision_axis_d2(d1, d2, offset_d1, offset_d2, is_negative1, is_negative2)\
    collide_with_chunk_d2(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis##_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, zox_axis##_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2);

#define handle_collision_axis(d, offset, is_negative)\
    collide_with_chunk(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis##_##d, collision_point_real.d,  position_last.d, offset.d, &did_collide##_##d, &collision_offset.d, is_negative);

#define detect_voxel_collisions()\
\
const float3 offset_left = float3_multiply_float(bounds3D->value, -1);\
const float3 offset_right = bounds3D->value;\
\
/* single axis collision, two sides per axis*/\
handle_collision_axis(x, offset_left, 1)\
handle_collision_axis(x, offset_right, 0)\
handle_collision_axis(y, offset_left, 1)\
handle_collision_axis(y, offset_right, 0)\
handle_collision_axis(z, offset_left, 1)\
handle_collision_axis(z, offset_right, 0)\
\
/* double axis collision, fours sides per two axis*/\
handle_collision_axis_d2(x, z, offset_left.x, offset_left.z, 1, 1)\
handle_collision_axis_d2(x, z, offset_right.x, offset_left.z, 0, 1)\
handle_collision_axis_d2(x, z, offset_left.x, offset_right.z, 1, 0)\
handle_collision_axis_d2(x, z, offset_right.x, offset_right.z, 0, 0)\
handle_collision_axis_d2(x, y, offset_left.x, offset_left.y, 1, 1)\
handle_collision_axis_d2(x, y, offset_right.x, offset_left.y, 0, 1)\
handle_collision_axis_d2(x, y, offset_left.x, offset_right.y, 1, 0)\
handle_collision_axis_d2(x, y, offset_right.x, offset_right.y, 0, 0)\
handle_collision_axis_d2(y, z, offset_left.y, offset_left.z, 1, 1)\
handle_collision_axis_d2(y, z, offset_right.y, offset_left.z, 0, 1)\
handle_collision_axis_d2(y, z, offset_left.y, offset_right.z, 1, 0)\
handle_collision_axis_d2(y, z, offset_right.y, offset_right.z, 0, 0)\
\
/* three axis collision*/\
handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_left.z, 1, 1, 1)\
handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_left.z, 0, 1, 1)\
handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_left.z, 1, 0, 1)\
handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_left.z, 0, 0, 1)\
handle_collision_axis_d3(x, y, z, offset_left.x, offset_left.y, offset_right.z, 1, 1, 0)\
handle_collision_axis_d3(x, y, z, offset_right.x, offset_left.y, offset_right.z, 0, 1, 0)\
handle_collision_axis_d3(x, y, z, offset_left.x, offset_right.y, offset_right.z, 1, 0, 0)\
handle_collision_axis_d3(x, y, z, offset_right.x, offset_right.y, offset_right.z, 0, 0, 0)



// Macros for handling 3-dimensional collisions
#define handle_collision_axis_d3(d1, d2, d3, offset_d1, offset_d2, offset_d3, is_negative1, is_negative2, is_negative3)\
    collide_with_chunk_d3(world, chunkLinks, max_depth, block_collisions, real_position_to_voxel_position(position_last, max_depth), zox_axis##_##d1, collision_point_real.d1, position_last.d1, offset_d1, &did_collide##_##d1, &collision_offset.d1, is_negative1, zox_axis##_##d2, collision_point_real.d2, position_last.d2, offset_d2, &did_collide##_##d2, &collision_offset.d2, is_negative2, zox_axis##_##d3, collision_point_real.d3, position_last.d3, offset_d3, &did_collide##_##d3, &collision_offset.d3, is_negative3);
