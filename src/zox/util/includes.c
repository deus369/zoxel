// base libraries we rely on besides ecs
#include <signal.h> // used for detecting cancel
#include <string.h> // who uses this?
#include <stdlib.h> // for malloc & free
#include <stdio.h>  // just for sprintf and perror
// sub modules
#include "../../core/core.c"
#ifndef zox_disable_inner_core
    #include "../../inner_core/inner_core.c"
    #include "../../users/users.c"
    #include "../../gameplay/gameplay.c"
    #include "../../space/space.c"
#endif
