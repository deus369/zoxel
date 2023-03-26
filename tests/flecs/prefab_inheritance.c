//! This script tests prefab inheritance.

// Build:
// cc -std=c99 -D_DEFAULT_SOURCE -o tests/flecs/test_prefab_inheritance imports/flecs.c tests/flecs/test_prefab_inheritance.c; ./tests/flecs/test_prefab_inheritance;

#include "../../include/flecs.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct {
    int value;
} Component;
ECS_COMPONENT_DECLARE(Component);

int main(int argc, char *argv[]) 
{
    ecs_world_t *world = ecs_init_w_args(argc, argv);
    ECS_COMPONENT_DEFINE(world, Component);
    ecs_entity_t prefab_a = ecs_new_prefab(world, "prefab_a");
    ecs_add(world, prefab_a, Component);
    ecs_entity_t entity_a = ecs_new_w_pair(world, EcsIsA, prefab_a);
    printf("Component exists, initially inherited? %s\n", ecs_has(world, entity_a, Component) ? "Yes" : "No");
    ecs_remove(world, entity_a, Component);
    printf("A Component exists after ecs_remove? %s\n", ecs_has(world, entity_a, Component) ? "Yes" : "No");
    ecs_remove_pair(world, entity_a, EcsIsA, prefab_a);
    ecs_remove(world, entity_a, Component);
    printf("A Component exists after ecs_remove_pair? %s\n", ecs_has(world, entity_a, Component) ? "Yes" : "No");
    ecs_entity_t entity_b = ecs_new_w_pair(world, EcsDontInherit, prefab_a);
    printf("B Component exists before ecs_remove (with EcsDontInherit)? %s\n", ecs_has(world, entity_b, Component) ? "Yes" : "No");
    ecs_remove(world, entity_b, Component);
    printf("B Component exists after ecs_remove (with EcsDontInherit)? %s\n", ecs_has(world, entity_b, Component) ? "Yes" : "No");
    
    printf("RESULT: SUCCESS\n");
    return 0;
}

/** Output is
* Testing [test_prefab_inheritance]
* Component exists, initially inherited? Yes
* A Component exists after ecs_remove? Yes
* A Component exists after ecs_remove_pair? No
* B Component exists after ecs_remove (with EcsDontInherit)? No
* Ended Testing [test_prefab_inheritance]
*/