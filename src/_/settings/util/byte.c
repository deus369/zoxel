// get
static inline byte zoxs_get_byte(const setting s) {
    return s.value_byte;
}

// limit
byte zoxs_limit_byte(ecs_world_t* world, const char *name, byte min, byte max) {
    for (int i = 0; i < settings_count; i++) {
        setting s = settings[i];
        if (strcmp(name, s.name) == 0) {
            if (s.type == zox_data_type_byte) {
                // zox_log("+ setting byte [%s] at [%i]", name, i)
                s.min_byte = min;
                s.max_byte = max;
                // now set again
                byte new_value = clampf(s.value_byte, s.min_byte, s.max_byte);
                if (new_value != s.value_byte) {
                    s.value_byte = new_value;
                    s.on_set(world, &new_value);
                    settings[i] = s;
                }
                settings[i] = s;
                return 1;
            }
        }
    }
    zox_log_error("? [byte] setting [%s]", name)
    return 0;
}

// set

byte zoxs_set_byte_silently(ecs_world_t *world, const char *name, byte value) {
    for (int i = 0; i < settings_count; i++) {
        setting s = settings[i];
        if (strcmp(name, s.name) == 0) {
            if (s.type == zox_data_type_byte) {
                byte has_limit = s.min_byte == s.max_byte;
                byte new_value = has_limit ? value : clampf(value, s.min_byte, s.max_byte);
                if (new_value != s.value_byte) {
                    s.value_byte = new_value;
                    settings[i] = s;
                    save_settings();
                }
                return 1;
            }
        }
    }
    zox_log_error("missing [byte] setting [%s]", name)
    return 0;
}

byte zoxs_set_byte(ecs_world_t *world, const char *name, byte value) {
    for (int i = 0; i < settings_count; i++) {
        setting s = settings[i];
        if (strcmp(name, s.name) == 0) {
            if (s.type == zox_data_type_byte) {
                byte has_limit = s.min_byte == s.max_byte;
                byte new_value = has_limit ? value : clampf(value, s.min_byte, s.max_byte);
                if (new_value != s.value_byte) {
                    s.value_byte = new_value;
                    s.on_set(world, &new_value);
                    settings[i] = s;
                    save_settings();
                }
                return 1;
            }
        }
    }
    zox_log_error("missing [byte] setting [%s]", name)
    return 0;
}

#define zoxs_new_byte_lim(name, function, value, min, max) {\
    zoxs_set(name, zox_data_type_byte, function);\
    zoxs_limit_byte(world, name, min, max);\
    zoxs_set_byte(world, name, value);\
}

#define zoxs_new_byte(name, function, value) {\
    zoxs_set(name, zox_data_type_byte, function);\
    zoxs_set_byte(world, name, value);\
}
