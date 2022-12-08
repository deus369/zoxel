//! This is to test change queries; expected result is only calling Changed when component has changed.
// cc -std=c99 -D_DEFAULT_SOURCE -o tests/builds/change_queries include/flecs.c tests/flecs/change_queries.c; ./tests/builds/change_queries;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

// macros, imported from zoxel
#define zoxel_component(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name)

#define zoxel_filter(name, world, ...)\
    ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { \
        .filter.expr = #__VA_ARGS__});
        
#define zoxel_system_ctx(world, id_, phase, ctx_, ...)\
{ \
    ecs_system_desc_t desc = {0}; \
    ecs_entity_desc_t edesc = {0}; \
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0); \
    edesc.add[1] = (phase); \
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__; \
    desc.callback = id_; \
    desc.multi_threaded = 1; \
    desc.ctx = ctx_; \
    ecs_id(id_) = ecs_system_init(world, &desc); \
} \
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

zoxel_component(TestComponent, int);

void TestChangeQuerySystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        printf("    - Not changed\n");
        return;
    }
    printf("    - Changed\n");
    ecs_world_t *world = it->world;
    const TestComponent *TestComponents = ecs_field(it, TestComponent, 1);
    for (int i = 0; i < it->count; i++)
    {
        ecs_entity_t e = it->entities[i];
    }
    // ecs_query_skip(it);
}
ECS_SYSTEM_DECLARE(TestChangeQuerySystem);

int main(int argc, char *argv[]) 
{
    printf("Testing change_queries.\n");
    // initialize world
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    // initialize component
    ECS_COMPONENT(world, TestComponent);
    // initialize system with change query
    zoxel_filter(change_query, world, [in] TestComponent);
    zoxel_system_ctx(world, TestChangeQuerySystem, EcsPostUpdate, change_query, [in] TestComponent);
    // add entities
    ecs_entity_t test_entity;
    for (int i = 0; i < 8; i++)
    {
        ecs_entity_t e = ecs_new_entity(world, "");
        ecs_set(world, e, TestComponent, { 0 });
        if (i == 0)
        {
            test_entity = e;
        }
    }
    // progress once
    for (int i = 0; i < 8; i++)
    {
        printf("ECS Progress [%i]\n", i);
        ecs_progress(world, 0);
        if (i == 5)
        {
            ecs_set(world, test_entity, TestComponent, { 3 });  // this should trigger change
        }
    }
    printf("RESULT: (lazymode) Check log.\n");
    return ecs_fini(world);
}