#ifndef zoxel_blueprints
#define zoxel_blueprints

zoxel_declare_tag(Blueprint)
zoxel_declare_tag(Bluenode)

void BlueprintsImport(ecs_world_t *world)
{
    zoxel_module(Blueprints)
    zoxel_define_tag(Blueprint)
    zoxel_define_tag(Bluenode)
}
#endif