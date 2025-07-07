#define zox_debug_id(component) {\
    const ecs_entity_t _id = zox_id(component);\
    if (!_id) {\
        zox_log_error("❌ %s is NOT registered", #component)\
    } else {\
        zox_log("✅ %s is registered [%s]", #component, zox_get_path(_id))\
    }\
}
