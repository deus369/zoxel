// todo: link the loaded files to ecs later
// when we loading files
zox_hook(files_load, (ecs_world_t* world), (world))

// for after we loaded stuff
zox_hook(on_boot, (ecs_world_t* world, ecs_entity_t app), (world, app))