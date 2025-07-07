#define zox_debug_id(component) {\
    const ecs_entity_t _id = zox_id(component);\
    if (!_id) {\
        zox_log_error("❌ %s is NOT registered in the world.", #component)\
    } else {\
        zox_log("✅ %s is registered. ID: %u", #component, (unsigned) _id)\
        zox_log("📛 %s", ecs_get_path_w_sep(world, 0, _id, ".", NULL))\
    }\
}
