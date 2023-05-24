//! This is to test change queries; expected result is only calling Changed when component has changed.
// cc -std=c99 -D_DEFAULT_SOURCE -o tests/builds/change_queries include/flecs.c tests/flecs/change_queries.c; ./tests/builds/change_queries;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

// macros, imported from zoxel
#define zox_component(name, type)\
typedef struct\
{\
    type value;\
} name;\
ECS_COMPONENT_DECLARE(name)

#define zoxel_filter(name, world, ...)\
    ecs_query_t *name = ecs_query_init(world, &(ecs_query_desc_t) { \
        .filter.expr = #__VA_ARGS__});
        
#define zoxel_system_ctx(id_, phase, ctx_, ...)\
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

zox_component(TestComponent, int);
zox_component(TestComponentA, bool);
zox_component(TestComponentB, bool);

void TestChangeQuerySystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    ecs_iter_t change_iter = ecs_query_iter(it->world, changeQuery);
    // This handles multiple tables
    while (ecs_query_next(&change_iter))
    {
        if (change_iter.table != it->table)
        {
            // if this is not the table currently iterated by the system, don't reset changed state
            ecs_query_skip(&change_iter);
        }
    }
    if (!ecs_query_changed(changeQuery, NULL))
    {
        printf("    - Not changed\n");
        return;
    }
    else
    {
        printf("    - Changed\n");
    }
}
ECS_SYSTEM_DECLARE(TestChangeQuerySystem);

int main(int argc, char *argv[]) 
{
    printf("Testing change_queries.\n");

    // initialize world
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    // initialize components
    ECS_COMPONENT(world, TestComponent);
    ECS_COMPONENT(world, TestComponentA);
    ECS_COMPONENT(world, TestComponentB);

    // initialize system with change query
    zoxel_filter(change_query, world, [in] TestComponent);
    zoxel_system_ctx(TestChangeQuerySystem, EcsPostUpdate, change_query, [in] TestComponent);

    // add entities
    ecs_entity_t test_entity;
    for (int i = 0; i < 8; i++)
    {
        ecs_entity_t e = ecs_new_entity(world, "");
        ecs_set(world, e, TestComponent, { 0 });
        if (i < 4)
        {
            ecs_set(world, e, TestComponentA, { true });
        }
        else
        {
            ecs_set(world, e, TestComponentB, { false });
        }
        if (i == 0)
        {
            test_entity = e;
        }
    }

    // progress system 8 times
    for (int i = 0; i < 8; i++)
    {
        printf("ECS Progress [%i]\n", i);
        ecs_progress(world, 0);
        if (i == 5)
        {
            printf("Changed TestComponent at [%i]\n", i);
            ecs_set(world, test_entity, TestComponent, { 3 });  // this should trigger change
        }
    }

    printf("RESULT: (lazymode) Check log.\n");
    return ecs_fini(world);
}

/** Expected Result:

Testing change_queries.
ECS Progress [0]
    - Changed
    - Changed
ECS Progress [1]
    - Not changed
    - Not changed
ECS Progress [2]
    - Not changed
    - Not changed
ECS Progress [3]
    - Not changed
    - Not changed
ECS Progress [4]
    - Not changed
    - Not changed
ECS Progress [5]
    - Not changed
    - Not changed
Changed TestComponent at [5]
ECS Progress [6]
    - Not changed
    - Not changed
ECS Progress [7]
    - Not changed
    - Not changed
RESULT: (lazymode) Check log.

Notes: This only works if the tables match between the change filter and the normal iterator
    A query will flag a table as changed if:
    - the component has changed for a table
    - the query hasn't iterated the table since the change

    This is an issue, if I have more components, does this flag the table as changed?
        - No it shouldn't be an issue. The tables flag per component. May need to test anyway? Later.
*/