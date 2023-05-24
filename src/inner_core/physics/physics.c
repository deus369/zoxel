#ifndef zoxel_physics
#define zoxel_physics

zox_declare_tag(Frictioned)
zox_byte_component(DisableMovement)
#ifdef zoxel_transforms2D
    #include "physics2D/physics2D.c"
#endif
#ifdef zoxel_transforms3D
    #include "physics3D/physics3D.c"
#endif

zox_begin_module(Physics)
zox_define_tag(Frictioned)
zox_define_component(DisableMovement)
#ifdef zoxel_transforms2D
    zox_import_module(Physics2D)
#endif
#ifdef zoxel_transforms3D
    zox_import_module(Physics3D)
#endif
zoxel_end_module(Physics)

#endif