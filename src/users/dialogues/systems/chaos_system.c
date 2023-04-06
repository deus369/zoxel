void ChaosSystem(ecs_iter_t *it) {
    const Fire *fires = ecs_field(it, Fire, 1);
    const Power *powers = ecs_field(it, Power, 2);
    Position *positions = ecs_field(it, Position, 3);
    Rotation *rotations = ecs_field(it, Rotation, 4);
    for (int i = 0; i < it->count; i++) {
          const Fire *fire = &fires[i];
          const Power *power = &powers[i];
          Position *position = &positions[i];
          Rotation *rotation = &rotations[i];
          // add your logic here
    }
}
zoxel_declare_system(ChaosSystem)
