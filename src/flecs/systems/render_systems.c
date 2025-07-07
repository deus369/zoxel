
#define zox_render2D_system(name, ...) {\
    if (!headless) {\
        zox_system_1(name, 0, __VA_ARGS__)\
        add_to_render2D_loop(ecs_id(name));\
    }\
}

#define zox_render3D_system(name, ...) {\
    if (!headless) {\
        zox_system_1(name, 0, __VA_ARGS__)\
        add_to_render3D_loop(ecs_id(name));\
    }\
}

#define zox_render3D_plus_system(name, ...) {\
if (!headless) {\
    zox_system_1(name, 0, __VA_ARGS__)\
    add_to_render3D_plus_loop(ecs_id(name));\
}\
}

#define zox_gpu_dispose_system(name, ...) {\
    if (!headless) {\
        zox_system_1(name, 0, __VA_ARGS__)\
        add_to_gpu_dispose_systems(ecs_id(name));\
    }\
}

#define zox_gpu_restore_system(name, ...) {\
    if (!headless) {\
        zox_system_1(name, 0, __VA_ARGS__)\
        add_to_gpu_restore_systems(ecs_id(name));\
    }\
}
