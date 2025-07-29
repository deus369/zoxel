const char* settings_game_name;
byte is_log_settings_io = 0;
byte is_log_save_settings = 0;
byte is_log_load_settings = 0;
byte has_loaded = 0;

// Helpers to find ~/.config/<appname>/settings.cfg
static const char* get_settings_file(const char *app_name) {
    static char final_path[2048];
    char base_path[1024];
    const char* xdg = getenv("XDG_CONFIG_HOME");
    const char* home = getenv("HOME");
    if (xdg && *xdg) {
        snprintf(base_path, sizeof(base_path), "%s/%s", xdg, app_name);
    } else if (home && *home) {
        snprintf(base_path, sizeof(base_path), "%s/.config/%s", home, app_name);
    } else {
        return "./settings.cfg";
    }
#if zox_windows
    mkdir(base_path);
#else
    mkdir(base_path, 0755);
#endif
    snprintf(final_path, sizeof(final_path), "%s/settings.cfg", base_path);
    return final_path;
}

// Save all settings to disk as simple "name:type:value\n"
void save_settings() {
    if (!has_loaded) {
        // zox_log_error(" Trying to save before loaded...")
        return;
    }
    const char* app_name = settings_game_name;
    const char* fn = get_settings_file(app_name);
    FILE* f = fopen(fn, "w");
    if (!f) {
        zox_log_error("failed to open settings file [%s]: %s", fn, strerror(errno))
        return;
    }
    for (uint i = 0; i < settings_count; i++) {
        setting s = settings[i];
        switch (s.type) {
            case zox_data_type_byte:
                fprintf(f, "%s:byte:%u\n", s.name, s.value_byte);
                if (is_log_save_settings) {
                    zox_log("+ saved byte [%s] [%i]", s.name, s.value_byte)
                }
                break;
            case zox_data_type_int:
                fprintf(f, "%s:int:%d\n",  s.name, s.value_int);
                break;
            case zox_data_type_float:
                fprintf(f, "%s:float:%f\n",s.name, s.value_float);
                if (is_log_save_settings) {
                    zox_log("+ saved float [%s] [%i]", s.name, s.value_float)
                }
                break;
            case zox_data_type_string:
                // escape newlines or colons as needed!
                fprintf(f, "%s:string:%s\n",s.name, s.value_string);
                break;
        }
    }
    fclose(f);
    if (is_log_settings_io) {
        zox_log("> saved %u settings to %s", settings_count, fn)
    }
}

// Load and apply each setting, firing on_set as needed
extern const char* game_name;
void load_files_settings(ecs_world_t* world) {
    const char* app_name = game_name;
    settings_game_name = app_name;
    const char* fn = get_settings_file(app_name);
    FILE* f = fopen(fn, "r");
    if (!f) {
        if (is_log_settings_io) {
            zox_log("> no settings file at %s, skipping load", fn)
        }
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // trim newline
        line[strcspn(line, "\r\n")] = 0;
        char* name = strtok(line, ":");
        char* type = strtok(NULL, ":");
        char* val  = strtok(NULL, "");
        if (!name || !type || !val) {
            continue;
        }
        if (strcmp(type, "byte") == 0) {
            byte v = (byte)atoi(val);
            zoxs_set_byte(world, name, v);
            if (is_log_load_settings) {
                zox_log("- loaded byte [%s] [%i]", name, v)
            }
        } else if (strcmp(type, "int") == 0) {
            int v = atoi(val);
            zoxs_set_int(world, name, v);
        } else if (strcmp(type, "float") == 0) {
            float v = strtof(val, NULL);
            zoxs_set_float(world, name, v);
            if (is_log_load_settings) {
                zox_log("- loaded float [%s] [%i]", name, v)
            }
        } else if (strcmp(type, "string") == 0) {
            zoxs_set_string(world, name, val);
        }
    }
    fclose(f);
    if (is_log_settings_io) {
        zox_log("> loaded settings from %s", fn)
    }
    has_loaded = 1;
}
