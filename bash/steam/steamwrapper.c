#ifndef zox_steamwrapper
#define zox_steamwrapper

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char initialize_steam();

void shutdown_steam();

void authenticate_user();

const char* get_steam_user_name();

int get_friends_count();
uint64_t get_friend_id(int index);
const char* get_friend_name(uint64_t steam_id);

#ifdef __cplusplus
}
#endif

#endif
