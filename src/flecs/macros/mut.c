#define zox_get_mut(e, T)\
    ecs_get_mut(world, e, T);

#define zox_get_mutt(e, type, name)\
    type *name = zox_get_mut(e, type)

#define zox_modified(e, type)\
    ecs_modified(world, e, type);

#define zox_muter(e, type, name)\
    zox_get_mutt(e, type, name)\
    zox_modified(e, type)

#define zox_get_muter(e, type, name)\
    zox_muter(e, type, name)

#define zox_set_mut(e, type, valuer) {\
    type *component = zox_get_mut(e, type)\
    if (component->value != valuer) {\
        component->value = valuer;\
        zox_modified(e, type)\
    }\
}
