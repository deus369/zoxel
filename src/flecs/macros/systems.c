#define zox_declare_system(name)\
    ECS_SYSTEM_DECLARE(name);

#if defined(zox_enable_log_new_system) && !defined(zox_disable_logs)
    #define zox_log_new_system(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_new_system(msg, ...) { }
#endif

#ifdef zox_flecs_4

    #define zox_system(id_, phase, ...) { \
        ecs_entity_desc_t edesc = {0}; \
        ecs_id_t add_ids[3] = {\
            ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0), \
            (phase), \
            0 \
        };\
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add = add_ids;\
        ecs_system_desc_t desc = {0}; \
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = 1;\
        ecs_id(id_) = ecs_system_init(world, &desc); \
        zox_log_new_system("+ new system [%s]", #id_)\
    };

#else

    #define zox_system(id_, phase, ...) { \
        ecs_entity_desc_t edesc = {0}; \
        edesc.id = ecs_id(id_);\
        edesc.name = #id_;\
        edesc.add[0] = ((phase) ? ecs_pair(EcsDependsOn, (phase)) : 0);\
        edesc.add[1] = (phase);\
        ecs_system_desc_t desc = {0}; \
        desc.entity = ecs_entity_init(world, &edesc);\
        desc.query.filter.expr = #__VA_ARGS__; \
        desc.callback = id_; \
        desc.multi_threaded = 1;\
        ecs_id(id_) = ecs_system_init(world, &desc); \
        zox_log_new_system("+ new system [%s]", #id_)\
    };

#endif

#define zox_system_1(id_, phase, ...)\
    ECS_SYSTEM_DEFINE(world, id_, phase, __VA_ARGS__);\
    zox_log_new_system("+ new system_1 [%s]", #id_)

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

#define zox_texture_generation_system(texture_tag, system) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.core.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.core.TextureData, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture)\
}

#define zox_texture_system(system, tag, ...) {\
    zox_filter(textures, [out] textures.core.GenerateTexture, [none] tag)\
    zox_system_ctx(system, zox_pip_textures, textures, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture, [out] rendering.TextureDirty, [out] textures.core.TextureData, __VA_ARGS__, [none] tag)\
}

#define zox_texture_generation_system2(texture_tag, system, ...) {\
    zox_filter(generateTextureQuery, [none] texture_tag, [out] textures.core.GenerateTexture)\
    zox_system_ctx(system, zox_pip_textures, generateTextureQuery, [none] texture_tag, [out] rendering.TextureDirty, [out] textures.core.TextureData, [in] textures.core.TextureSize, [out] textures.core.GenerateTexture, __VA_ARGS__)\
}
