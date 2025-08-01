// get
static inline float zoxs_get_float(const setting s) {
    return s.value_float;
}

// limit
byte zoxs_limit_float(ecs_world_t* world, const char *name, float min, float max) {
    for (uint i = 0; i < settings_count; i++) {
        setting s = settings[i];
        if (strcmp(name, s.name) == 0) {
            if (s.type == zox_data_type_float) {
                s.min_float = min;
                s.max_float = max;
                // now set again
                float new_value = clampf(s.value_float, s.min_float, s.max_float);
                if (new_value != s.value_float) {
                    s.value_float = new_value;
                    s.on_set(world, &new_value);
                    settings[i] = s;
                }
                settings[i] = s;
                return 1;
            }
        }
    }
    zox_log_error("? [float] setting [%s]", name)
    return 0;
}

// set
byte zoxs_set_float(ecs_world_t *world, const char *name, float value) {
    for (uint i = 0; i < settings_count; i++) {
        setting s = settings[i];
        if (strcmp(name, s.name) == 0) {
            if (s.type == zox_data_type_float) {
                float new_value = clampf(value, s.min_float, s.max_float);
                if (new_value != s.value_float) {
                    s.value_float = new_value;
                    s.on_set(world, &new_value);
                    settings[i] = s;
                    save_settings();
                }
                return 1;
            }
        }
    }
    zox_log_error("missing [float] setting [%s]", name)
    return 0;
}

#define zoxs_new_float_lim(name, function, value, min, max) {\
    zoxs_set(name, zox_data_type_float, function);\
    zoxs_limit_float(world, name, min, max);\
    zoxs_set_float(world, name, value);\
}

#define zoxs_new_float(name, function, value) {\
    zoxs_set(name, zox_data_type_float, function);\
    zoxs_set_float(world, name, value);\
}
