#define zox_component_array(name, type, length)\
    const byte name##_length = length;\
    typedef struct {\
        type value[length];\
    } name;\
    zox_custom_component(name)

// placeholder for later
#define zox_define_component_array(name)\
    zox_define_component(name)

#define zox_component_array_l(name, type, capacity) \
    const ulong name##_length = capacity; \
    typedef struct { \
        ulong length; \
        type value[capacity]; \
    } name; \
    zox_custom_component(name)

// placeholder for later
#define zox_define_component_array_l(name)\
    zox_define_component(name)
