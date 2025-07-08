#define zox_link_component(name, type, links_name, ...)\
    zox_component(name, type)\
    void on_destroyed##_##name(ecs_iter_t *it) {\
        zox_field_world()\
        name *components = ecs_field(it, name, 1);\
        for (int i = 0; i < it->count; i++) {\
            zox_field_e()\
            name *component = &components[i];\
            if (component->value && zox_valid(component->value)) {\
                zox_muter(component->value, links_name, links_component)\
                remove_from_##links_name(links_component, e);\
            }\
            component->value = 0;\
        }\
    }

#define zox_define_links_component2(name, ...)\
    zox_define_component(name)\
    zox_observe(on_destroyed_##name, EcsOnRemove, __VA_ARGS__)

#define zox_define_links_component(name)\
    zox_define_links_component2(name, [out] name)
