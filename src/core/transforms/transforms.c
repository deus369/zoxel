#ifndef zoxel_transforms
#define zoxel_transforms

zoxel_component(Scale1D, float)     //! Scales an entities transform in 1D.
#include "hierarchy/hierarchy.c"
#include "transforms2D/transforms2D.c"
#include "transforms3D/transforms3D.c"

zoxel_begin_module(Transforms)
zoxel_define_component(Scale1D)
zoxel_import_module(Hierarchys)
zoxel_import_module(Transforms2D)
zoxel_import_module(Transforms3D)
zoxel_end_module(Transforms)

#endif