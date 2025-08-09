#define zoxc_link(name, type, links_name, ...)\
    zoxc(name, type); \
    void on_destroyed_##name(ecs_iter_t *it) {\
        zox_sys_world(); \
        zox_sys_begin(); \
        zox_sys_out(name); \
        for (int i = 0; i < it->count; i++) {\
            zox_sys_e(); \
            zox_sys_o(name, component); \
            if (component->value && zox_valid(component->value)) { \
                zox_muter(component->value, links_name, links_component); \
                remove_from_##links_name(links_component, e); \
            } \
            component->value = 0; \
        } \
    }

#define zox_define_links_component2(name, ...)\
    zox_define_component(name);\
    zox_observe(on_destroyed_##name, EcsOnRemove, __VA_ARGS__)

#define zox_define_links_component(name)\
    zox_define_links_component2(name, [out] name)
