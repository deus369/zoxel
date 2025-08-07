#ifndef zoxm_streaming
#define zoxm_streaming

#include "settings/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "systems/_.c"

zox_begin_module(Streaming)
    define_components_streaming(world);
    define_systems_streaming(world);
    initialize_settings_streaming(world);
zox_end_module(Streaming)

#endif