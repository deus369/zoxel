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
zox_end_module(Skills)

#endif

// todo: damage popups
// todo: screenshake on melee hit
// todo: small jump forward towards target when hitting them
// todo: time damage during hit, not just instant
// remember: when spawned in similar pipeline, it didn't recognize components in a system also in that system, it removed dots straight away because of this..
// sepserate damage logic
// print who kills who
// todo: Aura Skill Entity to remember list of effected characters?
// todo: need ally system
// zox_declare_user_data(Skill)