// Zox settings
//
// void on_set_float(ecs_world_t*world, void* value) {
//     float valuef = *(float*) value;
//     zox_log("> brightness was set to %f", valuef)
// }
//
// zox_begin_module(ModuleName)
//     zoxs_set("brightness", zox_data_type_float, &on_brightness_set);
//     zoxs_set_float("brightness", 0.75f);
//     setting s = zoxs_get("brightness");
//     zox_log("Current brightness: %f\n", zoxs_get_float(s));
// zox_end_module(ModuleName)
//
#include "data/_.c"
#define max_settings 256
uint settings_count = 0;
setting settings[max_settings];

// # New Settings #
void zoxs_set(const char* name, byte type, on_set_event on_set) {
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

setting zoxs_get(const char *name) {
    for (uint i = 0; i < settings_count; i++) {
        setting setting = settings[i];
        if (!strcmp(name, setting.name)) {
            // zox_log("found %s at [%i]", name, i)
            return setting;
        }
    }
    return (setting) { };
}

#include "util/_.c"