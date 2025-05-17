#if !defined(zox_mod_skills) && defined(zox_mod_users)
#define zox_mod_skills

#include "data/components.c"
#include "prefabs/prefabs.c"
#include "util/realm_skills.c"
#include "util/character_skills.c"
#include "systems/systems.c"
#include "ui/ui.c"

zox_begin_module(Skills)
    define_components_skills(world);
    define_systems_skills(world);
    zox_import_module(UISkills)
    spawn_prefabs_skills(world);
    add_hook_spawned_character3D(&spawn_character_skills);
zox_end_module(Skills)

#endif