#define zoxel_filter(name, world, ...)\
ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { .filter.expr = #__VA_ARGS__});

#define zoxel_add(world, entity, T)\
    ecs_add(world, entity, T);\
    ecs_override(world, entity, T);

#define zoxel_remove(entity, T) ecs_remove(world, entity, T);

#define zoxel_add_new(world, entity, T, ...)\
    ecs_set_id(world, entity, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, entity, ecs_id(T));

#define zoxel_set(world, entity, T, ...)\
    ecs_set_id(world, entity, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, entity, ecs_id(T));

#define zoxel_add_tag(entity, T)\
    ecs_add_id(world, entity, ecs_id(T));

//! Creates a simple Filter with components.
//! Adds a component but also adds override to an entity.
//! Adds a simple tag to an entity.
// printf("Component has reset [%lu].\n", (long int) it->entities[i]);
//! Adds a component with data and also adds override to an entity.
// todo: remove override id from here, as it should only be done for the prefab
// ecs_entity_t ecs_module_init(
//! My own flecs macros
// Remember it will destroy the prefab ones too... *facepalm*
// sizeof(type);    // 4 color
// sizeof(component->value); // 8, presumably pointer takes 4 more bytes?
// printf("Stride %i\n", stride);
// ecs_add_id(world, entity, ecs_id(T));
// ecs_override_id(world, entity, ecs_id(T))