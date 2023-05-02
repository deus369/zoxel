# flecs quirks

    my internal guide to remember what doesn't work with flecs

-----

## component data and spawning

- by default entitys using a prefab don't copy new component data in memory
        - i had to make my own macros to make it work like unity ecs (zoxel_set, zoxel_add)

## change filtering

- table change checks don't work in multithreaded mode, only single threaded
    - adding the line below to a system
    - if (!ecs_query_changed(NULL, it)) return;

- change checks don't seem to work atm for filters in single or multithreaded mode
    - adding the line below to a system, with a filter as input to that system
    - if (!ecs_query_changed(it->ctx, NULL)) return;

- ecs_query_skip doesn't work in multithreaded mode, it won't skip table changes there
    - tested this using zoxel_system and zoxel_system_1 (multi vs single thread)

- adding single threaded systems seems to tank my frame rates

-----

[Back](../readme.md)