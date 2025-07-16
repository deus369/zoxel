// Zox settings
//
// void on_set_float(ecs_world_t*world, void* value) {
//     float valuef = *(float*) value;
//     zox_log("> brightness was set to %f", valuef)
// }
//
// zox_begin_module(ModuleName)
//     zox_sset("brightness", zox_data_type_float, &on_brightness_set);
//     zox_sset_float("brightness", 0.75f);
//     setting s = zox_sget("brightness");
//     zox_log("Current brightness: %f\n", zox_sget_float(s));
// zox_end_module(ModuleName)
//
#include "data/_.c"
#define max_settings 256
uint settings_count = 0;
setting settings[max_settings];
#include "util/_.c"

// # New Settings #

void zox_sset(const char* name, byte type, on_set_event on_set) {
    if (settings_count >= max_settings) {
        zox_log_error("settings count already at its limit of [%i]", max_settings)
        return;
    }
    setting value = {
        .name = name,
        .type = type,
        .on_set = on_set,
    };
    settings[settings_count] = value;
    settings_count++;
}

setting zox_sget(const char *name) {
    for (int i = 0; i < settings_count; i++) {
        setting setting = settings[i];
        if (!strcmp(name, setting.name)) {
            // zox_log("found %s at [%i]", name, i)
            return setting;
        }
    }
    return (setting) { };
}

// # Getting Settings #
static inline byte zox_sget_byte(const setting s) {
    return s.value_byte;
}

static inline int zox_sget_int(const setting s) {
    return s.value_int;
}

static inline const char* zox_sget_string(const setting s) {
    return s.value_string;
}

// # Setting Settings #

byte zox_sset_byte(ecs_world_t *world, const char *name, byte value) {
    for (int i = 0; i < settings_count; i++) {
        setting setting = settings[i];
        if (strcmp(name, setting.name) == 0) {
            // zox_log("+ setting byte [%s] at [%i]", name, i)
            if (setting.type == zox_data_type_byte) {
                setting.value_byte = value;
                setting.on_set(world, &value);
                settings[i] = setting;
                return 1;
            }
        }
    }
    zox_log_error("missing [byte] setting [%s]", name)
    return 0;
}

byte zox_sset_int(ecs_world_t *world, const char *name, int value) {
    for (int i = 0; i < settings_count; i++) {
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

byte zox_sset_string(ecs_world_t *world, const char *name, const char* value) {
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