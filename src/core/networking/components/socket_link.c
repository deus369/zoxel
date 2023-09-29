zox_component(SocketLink, int)

void set_new_socket(ecs_world_t *world, ecs_entity_t e, int port) {
    zox_set(e, SocketLink, { open_socket(port) })
}

ECS_DTOR(SocketLink, ptr, {
    if (ptr->value != -1) {
        // zoxel_log(" > closing socket [%i]\n", ptr->value);
        if (close(ptr->value) < 0) perror(" ! [SocketLink] failed to close");
        ptr->value = -1;
    }
})