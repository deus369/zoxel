// #define zox_debug_modules
#define zox_module(name) ECS_MODULE(world, name);
#define zox_import_module(name) ECS_IMPORT(world, name);

void zox_debug_module2(ecs_world_t *world, const char *name, const ecs_entity_t module_type) {
    zox_log(" + module [%s] > [%s]\n", name, zox_get_name(module_type))
}

#define zox_debug_single_module(name)\
    zox_debug_module2(world, #name, ecs_id(name));

//  zox_log(" > Physics Module [%s]\n", zox_get_name_type(Physics))
void zox_debug_module(ecs_world_t *world, const char *name, const ecs_entity_t module_type) {
#ifdef zox_debug_modules
    zox_log(" + module [%s] > [%s]\n", name, zox_get_name(module_type))
#endif
}

#define zox_begin_module(name) void name##Import(ecs_world_t *world) {\
    zox_module(name)\
    zox_debug_module(world, #name, ecs_id(name));

#define zox_end_module(name)}

#define zox_module_dispose(function_name)\
    ecs_atfini(world, function_name, NULL);
