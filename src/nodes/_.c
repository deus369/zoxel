// generic nodes, used by blueprints and neurals and quests etc
#ifndef zoxm_nodes
#define zoxm_nodes

zox_tag(Node);
zox_tag(Nodelink);
zox_tag(Nodegraph);
zoxc_entity(NodeParent);
zoxc_entity(NodeNext);
#include "prefabs/prefabs.c"

zox_begin_module(Nodes)
    zox_define_tag(Node);
    zox_define_tag(Nodelink);
    zox_define_tag(Nodegraph);
    zox_define_component_entity(NodeParent);
    zox_define_component_entity(NodeNext);
    spawn_prefabs_nodes(world);
    // test_nodes(world);
zox_end_module(Nodes)

#endif
