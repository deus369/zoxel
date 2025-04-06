#ifndef zox_mod_zexts
#define zox_mod_zexts

zox_declare_tag(Zext)
zox_declare_tag(ZextLabel)
zox_declare_tag(ZextRenderEnabler)
zox_declare_tag(Text2D)
zox_component_byte(ZextDirty)
zox_component_byte(ZextAlignment)
zox_component_int(TextSize)
zox_component_byte2(TextPadding)
zox_component_double(AnimateZext)
zox_component_zext(TextData)
#include "data/settings.c"
#include "data/zext_update.c"
#include "data/zext_spawn_data.c"
#include "util/zigel_util.c"
#include "util/resize_util.c"
#include "prefabs/prefabs.c"
#include "util/zext_util.c"
#include "systems/systems.c"

zox_begin_module(Zexts)
    zox_define_tag(Zext)
    zox_define_tag(ZextLabel)
    zox_define_tag(ZextRenderEnabler)
    zox_define_tag(Text2D)
    zox_define_component_byte(ZextDirty)
    zox_define_component_byte(ZextAlignment)
    zox_define_component_int(TextSize)
    zox_define_component_byte2(TextPadding)
    zox_define_component_double(AnimateZext)
    zox_define_component_zext(TextData)
    define_systems_texts(world);
    spawn_prefabs_texts(world);
zox_end_module(Zexts)

#endif
