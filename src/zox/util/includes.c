// base libraries we rely on besides ecs
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror
// sub modules
#include "../../core/core.c"
#include "game_store_util.c"
#include "../../inner_core/inner_core.c"
#include "../../outer_core/outer_core.c"
#include "../../users/users.c"
#include "../../gameplay/gameplay.c"
#include "../../space/space.c"
