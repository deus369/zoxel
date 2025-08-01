// how to hook:
//  - call initialize_hook_##name in module
//  - call dispose_hook_##name in module_dispose
//  - call add_hook_##name in hooking  modules
//  - call run_hook_##name in function where we want to hook into

// todo: whenever define, add to initialize / dispose events for our core module (so i dont have to manually add those)

#define unwrap_args(...) __VA_ARGS__

#define zox_hookr(name, return_type, args_decl, arg_names)\
zox_event_type(hook_##name, return_type, unwrap_args args_decl)\
zoxel_dynamic_array(hook_##name)\
hook_##name##_array_d* functions_##name;\
\
void initialize_hook_##name() { \
    functions_##name = create_hook_##name##_array_d(initial_dynamic_array_size); \
}\
\
void dispose_hook_##name() { \
    dispose_hook_##name##_array_d(functions_##name); \
} \
\
void add_hook_##name(return_type (*event) args_decl) {\
    if (!functions_##name) {\
        zox_log_error("hook [%s] not initialized yet", #name)\
    } else {\
        hook_##name fun_event = (hook_##name) { event }; \
        add_to_hook_##name##_array_d(functions_##name, fun_event); \
    }\
}\
\
void run_hook_##name args_decl { \
    for (size_t i = 0; i < functions_##name->size; i++) { \
        if (functions_##name->data[i].value != NULL) { \
            (*functions_##name->data[i].value) arg_names; \
        } \
    } \
}


#define zox_hook(name, args_decl, arg_names)\
    zox_hookr(name, void, args_decl, arg_names)


/*#define zox_hook(name, args_decl, arg_names) \
    void initialize_functions_##name() { } \
    void dispose_functions_##name() { }\
    void add_functions_##name(void (*event) args_decl) { } \
    void run_functions_##name args_decl { zox_log("Running hook " #name " with args: " #arg_names "\n")}*/
