// zoxel shorthand for a module definition
#define zoxel_module(name)\
    ECS_MODULE(world, name);

#define zoxel_import_module(name)\
    ECS_IMPORT(world, name);

// I can override these macros during testing to print statements
//      When it breaks on module import

#define zoxel_begin_module(name)\
void name##Import(ecs_world_t *world) {\
    zoxel_module(name)

#define zoxel_end_module(name)}

/*
#define zoxel_module(world, id, moduleName)\
ecs_entity_t ecs_id(id) = 0;\
{\
    ecs_component_desc_t desc = {0};\
    desc.entity = ecs_id(id);\
    ecs_id(id) = ecs_module_init(world, moduleName, &desc);\
    ecs_set_scope(world, ecs_id(id));\
}\
(void)ecs_id(id);
*/