#if !defined(zox_mod_skills) && defined(zox_mod_users)
#define zox_mod_skills

#include "data/_.c"
#include "components/_.c"
#include "prefabs/_.c"
#include "spawn/_.c"
#include "util/_.c"
#include "systems/_.c"
#include "ui/ui.c"
#include "tests/aura.c"

zox_begin_module(Skills)
    define_components_skills(world);
    define_systems_skills(world);
    add_hook_spawned_character3D(&spawn_character_skills);
    spawn_prefabs_skills(world);
    zox_import_module(UISkills)
zox_end_module(Skills)

#endif