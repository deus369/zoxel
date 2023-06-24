#include <unistd.h> // close function kept here

//! Links to a opened socket.
zox_component(SocketLink, int)

void set_new_socket(ecs_world_t *world, ecs_entity_t e, int port) {
    ecs_set(world, e, SocketLink, { open_socket(port) });
}

ECS_DTOR(SocketLink, ptr, {
    if (ptr->value != -1) {
        if (close(ptr->value) < 0) {
            perror("SocketLink close");
        }
    }
})