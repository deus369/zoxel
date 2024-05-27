#include "brain.c"
#include "neuron.c"
#include "connection.c"
ecs_entity_t prefab_neuron;
ecs_entity_t prefab_connection;
ecs_entity_t prefab_brain;

void spawn_prefabs_neurals(ecs_world_t *world) {
    prefab_neuron = spawn_prefab_neuron(world);
    prefab_connection = spawn_prefab_connection(world);
    prefab_brain = spawn_prefab_brain(world);
}
