#include "core/core.c"
#include "generic/generic.c"
#include "timing/timing.c"
#include "transforms/transforms.c"
#include "networking/networking.c"
#include "players/players.c"
#include "inputs/inputs.c"
#include "apps/apps.c"          // test removing sdl for engine stability
#include "files/files.c"        // uses sdl path function atm
#include "cameras/cameras.c"
#include "rendering/rendering.c"
#include "sounds/sounds.c"
#include "nodes/nodes.c"
#include "realms/realms.c"
#include "colors/colors.c"
#include "games/games.c"
#include "raycasts/raycasts.c"

// inner core


// todo: make these flat as well
#ifndef zox_disable_inner_core
    #include "textures/textures.c"
    #include "musics/musics.c"
    #include "animations/animations.c"
    #include "bones/bones.c"
    #include "ui/ui.c"
    #include "lines/lines.c"
    #include "plots/plots.c"
    #include "genetics/genetics.c"
    #include "neurals/neurals.c"
    #include "tiles/tiles.c"
    #include "voxels/voxels.c"
    #include "physics/physics.c"
    #include "cubes/cubes.c"
    #include "particles/particles.c"
    #include "blueprints/blueprints.c"
    #include "characters/characters.c"

    #include "users/users.c"
    #include "gameplay/gameplay.c"
    #include "space/space.c"
#endif
