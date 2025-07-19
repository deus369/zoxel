#define zox_component_array(name, type, length)\
    const byte name##_length = length;\
    typedef struct {\
        type value[length];\
    } name;\
    zox_custom_component(name)

// placeholder for later
#define zox_define_component_array(name)\
    zox_define_component(name)
