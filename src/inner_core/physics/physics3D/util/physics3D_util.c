void add_physics3D(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, Velocity3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Acceleration3D, { { 0, 0, 0 } });
    // zoxel_set(world, e, Gravity3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Gravity3D, { { 0.0f, 0.01f, 0.0f } });  // -
    float bound_value = 8.0f;
    zoxel_set(world, e, Bounds3D, { { bound_value, bound_value, bound_value } });
    // zoxel_set(world, e, Torque3D, { { 0, 0, 0, 0 } });
}