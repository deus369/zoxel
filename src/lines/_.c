#ifndef zoxm_lines
#define zoxm_lines

// todo: lines_ui should be seperate
// todo: add a purely lines2D that doesn't rely on UI transforms
zox_declare_tag(Line)
zox_component(LineThickness, float)
// #include "lines2/_.c"
#include "lines3/_.c"

zox_begin_module(Lines)
    zox_define_tag(Line)
    zox_define_component(LineThickness)
    // zox_import_module(Lines2D)
    zox_import_module(Lines3)
zox_end_module(Lines)

#endif
