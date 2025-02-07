// generic nodes, used by blueprints and neurals and quests etc
#ifndef zox_mod_nodes
#define zox_mod_nodes

zox_declare_tag(Node)
zox_declare_tag(Nodelink)
zox_declare_tag(Nodegraph)
zox_component_entity(NodeParent)
zox_component_entity(NodeNext)
#include "prefabs/prefabs.c"

zox_begin_module(Nodes)
    zox_define_tag(Node)
    zox_define_tag(Nodelink)
    zox_define_tag(Nodegraph)
    zox_define_component_entity(NodeParent)
    zox_define_component_entity(NodeNext)
    spawn_prefabs_nodes(world);
    // test_nodes(world);
zoxel_end_module(Nodes)

#endif
