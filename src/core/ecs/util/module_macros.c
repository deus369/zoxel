#define zox_module(name) ECS_MODULE(world, name);

#define zox_import_module(name) ECS_IMPORT(world, name);

#define zox_begin_module(name)\
void name##Import(ecs_world_t *world) {\
    zox_module(name)

#define zoxel_end_module(name)}
