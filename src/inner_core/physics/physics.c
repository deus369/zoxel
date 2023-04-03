#ifndef zoxel_physics
#define zoxel_physics

zoxel_declare_tag(Frictioned)
zoxel_byte_component(DisableMovement)
#ifdef zoxel_transforms2D
    #include "physics2D/physics2D.c"
#endif
#ifdef zoxel_transforms3D
    #include "physics3D/physics3D.c"
#endif

zoxel_begin_module(Physics)
zoxel_define_tag(Frictioned)
zoxel_define_component(DisableMovement)
#ifdef zoxel_transforms2D
    zoxel_import_module(Physics2D)
#endif
#ifdef zoxel_transforms3D
    zoxel_import_module(Physics3D)
#endif
zoxel_end_module(Physics)

#endif