#define mesh_state_none 0

// trigger_slow -> generate
#define mesh_state_trigger_slow 1
#define mesh_state_generate 2

// normal flow
#define mesh_state_trigger 2 // for non skeletons, we can trigger faster

// upload to gpu
#define mesh_state_upload 3
#define mesh_state_end 4
