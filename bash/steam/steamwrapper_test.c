#include "steamwrapper.c"
#include <stdio.h>
#include <stdint.h>

int main() {
    printf("    > initializing steam:\n");
    if (initialize_steam()) {
        printf("    > steamworks initialized\n");
        authenticate_user();
        printf("    > steam user name: %s\n", get_steam_user_name());
        printf("        > friends %i\n", get_friends_count());
        for (int i = 0; i < get_friends_count(); i++) {
            uint64_t id = get_friend_id(i);
            printf("            > %s\n", get_friend_name(id));
        }
        shutdown_steam();
    } else {
        printf("    ! failed to open steam\n");
        //int error = steam_get_error();
        //printf("Steam API Error: %i\n", error);
    }
    return 0;
}
