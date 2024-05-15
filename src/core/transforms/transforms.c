#ifndef zox_transforms
#define zox_transforms

zox_component_float(Scale1D)    // rename this to UniformScale, more english like
#include "hierarchy/hierarchy.c"
#include "transforms2D/transforms2D.c"
#include "transforms3D/transforms3D.c"

zox_begin_module(Transforms)
zox_define_component_float(Scale1D)
zox_import_module(Hierarchys)
zox_import_module(Transforms2D)
zox_import_module(Transforms3D)
zoxel_end_module(Transforms)

#endif
