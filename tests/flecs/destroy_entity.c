//! This script tests ecs_get_mut

// build line
// gcc -std=gnu99 -D_DEFAULT_SOURCE -o build/destroy_entity include/flecs/flecs.c tests/flecs/destroy_entity.c; ./build/destroy_entity;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

// adds multithreading
#define zox_system(id_, phase, ...) {\
    ecs_system_desc_t desc = {0};\
    ecs_entity_desc_t edesc = {0};\
    edesc.id = ecs_id(id_);\
    edesc.name = #id_;\
    edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
    edesc.add[1] = (phase);\
    desc.entity = ecs_entity_init(world, &edesc);\
    desc.query.filter.expr = #__VA_ARGS__;\
    desc.callback = id_;\
    desc.multi_threaded = 1;\
    ecs_id(id_) = ecs_system_init(world, &desc);\
}\
ecs_assert(ecs_id(id_) != 0, ECS_INVALID_PARAMETER, NULL);

/*typedef struct {
    bool value;
} DestroyMe;
ECS_COMPONENT_DECLARE(DestroyMe);*/

ECS_DECLARE(DestroyMe);

void DestroySystem(ecs_iter_t *it) {
    printf("        > DestroySystem [%i]\n", it->count);
    ecs_world_t *world = it->world;
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        printf("        > deleting entity [%lu]\n", e);
        ecs_delete(world, e);
    }
}
ECS_SYSTEM_DECLARE(DestroySystem);

int main(int argc, char *argv[]) {
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    ecs_set_threads(world, 8);
    // ECS_COMPONENT(world, DestroyMe);
    ECS_TAG_DEFINE(world, DestroyMe);
    zox_system(DestroySystem, EcsPreStore, [none] DestroyMe);
    // add e
    ecs_entity_t e = ecs_new_entity(world, "");
    ecs_add(world, e, DestroyMe);
    // progress once
    printf("    > pre system run [%i]\n", ecs_count(world, DestroyMe));
    ecs_progress(world, 0.1);
    printf("    > post system run [%i]\n", ecs_count(world, DestroyMe));
    printf("    > is e alive? [%s]\n", ecs_is_alive(world, e) ? "alive" : "dead");
    // progress twonce
    ecs_progress(world, 0.1);
    printf("    > system run 2nd time [%i]\n", ecs_count(world, DestroyMe));
    // le end
    printf("    > result [%s]\n", ecs_is_alive(world, e) ? "failure" : "success");
    return ecs_fini(world);
}