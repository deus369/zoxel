// #define zox_debug_modules
#define zox_module(name) ECS_MODULE(world, name);
#define zox_import_module(name) ECS_IMPORT(world, name);

//  zox_log(" > Physics Module [%s]\n", zox_get_name_type(Physics))
void zox_debug_module(ecs_world_t *world, const char *name, const ecs_entity_t module_type) {
#ifdef zox_debug_modules
    zox_log(" + module [%s] > [%s]\n", name, zox_get_name(module_type))
#endif
}

#define zox_begin_module(name) void name##Import(ecs_world_t *world) {\
    zox_module(name)\
    zox_debug_module(world, #name, ecs_id(name));

#define zoxel_end_module(name)}
