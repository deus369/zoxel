#define zox_field_world()\
    ecs_world_t *world = it->world;

#define zox_field_in(component_name, name, index)\
    const component_name *name = ecs_field(it, component_name, index);

#define zox_field_out(component_name, name, index)\
    component_name *name = ecs_field(it, component_name, index);

#define zox_field_in_iter(iter, component_name, name, index)\
    const component_name *name = ecs_field(iter, component_name, index);

#define zox_field_out_iter(iter, component_name, name, index)\
    component_name *name = ecs_field(iter, component_name, index);

#define zox_field_i(component_name, field_name, variable_name)\
    const component_name *variable_name = &field_name[i];

#define zox_field_o(component_name, field_name, variable_name)\
    component_name *variable_name = &field_name[i];

#define zox_field_e()\
    const ecs_entity_t e = it->entities[i];

// new

#define zox_sys_world()\
    ecs_world_t *world = it->world;

#define zox_sys_e()\
    const ecs_entity_t e = it->entities[i];

#define zox_sys_begin()\
    byte fi = 0;

#define zox_sys_in(name)\
    const name *name##s = ecs_field(it, name, ++fi);

#define zox_sys_out(name)\
    name *name##s = ecs_field(it, name, ++fi);

#define zox_sys_i(name, variable_name)\
    const name *variable_name = &name##s[i];

#define zox_sys_o(name, variable_name)\
    name *variable_name = &name##s[i];


// Second Iterator!

#define zox_sys_e_2()\
    const ecs_entity_t e2 = it2.entities[j];

#define zox_sys_begin_2()\
    byte fi2 = 0;

#define zox_sys_in_2(name)\
    const name *name##s_2 = ecs_field(&it2, name, ++fi2);

#define zox_sys_i_2(name, variable_name)\
    const name *variable_name = &name##s_2[j];

#define zox_sys_out_2(name)\
    name *name##s_2 = ecs_field(&it2, name, ++fi2);

#define zox_sys_o_2(name, variable_name)\
    name *variable_name = &name##s_2[j];
