//! My own flecs macros
// Remember it will destroy the prefab ones too... *facepalm*

// sizeof(type);    // 4 color
// sizeof(component->value); // 8, presumably pointer takes 4 more bytes?
// printf("Stride %i\n", stride);

//! Creates a simple Filter with components.
#define zoxel_filter(name, world, ...)\
    ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { \
        .filter.expr = #__VA_ARGS__});

// ecs_entity_t ecs_module_init(

//! Adds a component but also adds override to an entity.
#define zoxel_add(world, entity, T)\
    ecs_add(world, entity, T);\
    ecs_override(world, entity, T);

#define zoxel_remove(entity, T)\
    ecs_remove(world, entity, T);

// ecs_add_id(world, entity, ecs_id(T));
// ecs_override_id(world, entity, ecs_id(T))

//! Adds a component with data and also adds override to an entity.
#define zoxel_set(world, entity, T, ...)\
    ecs_set_id(world, entity, ecs_id(T), sizeof(T), &(T)__VA_ARGS__);\
    ecs_override_id(world, entity, ecs_id(T));

//! Adds a simple tag to an entity.
#define zoxel_add_tag(world, entity, T)\
    ecs_add_id(world, entity, ecs_id(T));
// printf("Component has reset [%lu].\n", (long int) it->entities[i]);