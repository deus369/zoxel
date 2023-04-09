void add_physics3D_basic(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, Velocity3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Acceleration3D, { { 0, 0, 0 } });
    zoxel_set(world, e, Gravity3D, { { 0.0f, physics3D_gravity, 0.0f } });
    zoxel_set(world, e, InitializePhysics3D, { 0 });
}

void add_physics3D(ecs_world_t *world, ecs_entity_t e) {
    add_physics3D_basic(world, e);
    float bound_value = 8.0f;
    zoxel_set(world, e, Bounds3D, { { bound_value, bound_value, bound_value } });
    // zoxel_set(world, e, Torque3D, { { 0, 0, 0, 0 } });
}