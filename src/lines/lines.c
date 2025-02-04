#ifndef zox_mod_lines
#define zox_mod_lines

zox_declare_tag(Line)
zox_component(LineThickness, float)
#include "lines2D/lines2D.c"
#include "lines3D/lines3D.c"

zox_begin_module(Lines)
zox_define_tag(Line)
zox_define_component(LineThickness)
zox_import_module(Lines2D)
zox_import_module(Lines3D)
zoxel_end_module(Lines)

#endif
