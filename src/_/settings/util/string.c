static inline const char* zoxs_get_string(const setting s) {
    return s.value_string;
}

byte zoxs_set_string(ecs_world_t *world, const char *name, const char* value) {
    for (int i = 0; i < settings_count; i++) {
        setting setting = settings[i];
        if (strcmp(name, setting.name) == 0) {
            // zox_log("+ setting string [%s] at [%i]", name, i)
            if (setting.type == zox_data_type_string) {
                setting.value_string = value;
                setting.on_set(world, &value);
                settings[i] = setting;
                return 1;
            }
        }
    }
    zox_log_error("missing [string] setting [%s]", name)
    return 0;
}
