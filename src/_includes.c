// pre engine defines
#include "zox/data/build_settings.c"
#include "zox/data/build_disables.c"
#include "zox/data/define_groups.c"
#include "zox/util/defines.c"
#include zox_nexus_defines

// engine modules
#include "core/core.c"

// todo: include all these automatically
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "players/players.c"
#include "inputs/inputs.c"
#include "apps/apps.c"          // test removing sdl for engine stability
#include "sdl/sdl.c"
#include "assets/assets.c"        // uses sdl path function atm
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "sounds/sounds.c"
#include "nodes/nodes.c"
#include "realms/realms.c"
#include "colors/colors.c"
#include "games/games.c"
#include "raycasts/raycasts.c"
// inner core
#include "textures/textures.c"
#include "musics/musics.c"
#include "animations/animations.c"
#include "bones/bones.c"
#include "ui/ui.c"
#include "game_ui/game_ui.c"
#include "lines/lines.c"
#include "plots/plots.c"
#include "genetics/genetics.c"
#include "neurals/neurals.c"
#include "cubes/cubes.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"
#include "voxes/voxes.c"
#include "weathers/weathers.c"
#include "terrain/terrain.c"
#include "physics/physics.c"
#include "particles/particles.c"
#include "blueprints/blueprints.c"
#include "characters/characters.c"
#include "dungeons/dungeons.c"
// user data
#include "users/users.c"
#include "combat/combat.c"
#include "stats/stats.c"
#include "items/items.c"
#include "skills/skills.c"
#include "actions/actions.c"
#include "dialogues/dialogues.c"
#include "quests/quests.c"
#include "classes/classes.c"
#include "jobs/jobs.c"
#include "races/races.c"
#include "clans/clans.c"
#include "lores/lores.c"
#include "achievements/achievements.c"
#include "users/util/post_users.c"
// gameplay
#include "pickups/pickups.c"
#include "crafting/crafting.c"
#include "farming/farming.c"
#include "turrets/turrets.c"
#include "combat/combat.c"
#include "maps/maps.c"
#include "ai/ai.c"
// on top
#include "editor_ui/editor_ui.c"
#include "controllers/controllers.c"
#include "space/space.c"
#include "debug/debug.c"