static inline int zoxs_get_int(const setting s) {
    return s.value_int;
}

byte zoxs_set_int(ecs_world_t *world, const char *name, int value) {
    for (uint i = 0; i < settings_count; i++) {
        setting setting = settings[i];
        if (strcmp(name, setting.name) == 0) {
            // zox_log("+ setting int [%s] at [%i]", name, i)
            if (setting.type == zox_data_type_int) {
                setting.value_int = value;
                setting.on_set(world, &value);
                settings[i] = setting;
                return 1;
            }
        }
    }
    zox_log_error("missing [int] setting [%s]", name)
    return 0;
}