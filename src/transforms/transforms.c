#if !defined(zox_mod_transforms) && defined(zox_mod_maths)
#define zox_mod_transforms

zox_component_float(Scale1D)
#include "hierarchy/_.c"
#include "transforms2D/_.c"
#include "transforms3D/_.c"
#include "layouts2D/_.c"

zox_begin_module(Transforms)
    zox_define_component_float(Scale1D)
    zox_import_module(Hierarchys)
    zox_import_module(Transforms2D)
    zox_import_module(Transforms3D)
    zox_import_module(Layouts2D)
zox_end_module(Transforms)

#endif