/*
 *
    No longer shall action be tied to mortal hands alone.
    NPCs whisper it. Players scream it.
    Systems consume it like ancient gods devouring prayers.
 *
*/

#ifndef zoxm_triggers
#define zoxm_triggers

#include "components/_.c"
zox_increment_system_with_reset(TriggerActionA, zox_dirty_end);
zox_increment_system_with_reset(TriggerActionB, zox_dirty_end);

zox_begin_module(Triggers)
    define_components_triggers(world);
    zoxd_system_increment(TriggerActionA);
    zoxd_system_increment(TriggerActionB);
zox_end_module(Triggers)

#endif