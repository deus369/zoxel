// g++ -shared -o lib/libsteam_wrapper.so steam_wrapper.cpp -Iinclude/steam -Llib -lsteam_api
#include "../../include/steam/steam_api.h"
#include "steamwrapper.c"
#include <stdlib.h>
// #include <stdexcept>
// #include <iostream>  // For demonstration purposes
// #include <cstdint>  // Include this header for uint64_t

unsigned char initialize_steam() {
    return SteamAPI_Init();
}

void shutdown_steam() {
    SteamAPI_Shutdown();
}

CSteamID get_steam_id() {
    CSteamID steamID = SteamUser()->GetSteamID();
    return steamID;
}

unsigned char is_logged_on() {
    return SteamUser()->BLoggedOn();
}

void authenticate_user() {
    // SteamUser()->LogOn(new CSteamID(), k_EAccountTypeIndividual);
    // SteamUser()->LogOn(get_steam_id(), k_EAccountTypeIndividual);
    if (!is_logged_on()) {
        // SteamUser()->LogOnAnonymous();
    }
}

void show_leaderboard() {
    // SteamUserStats()->RequestCurrentStats();
    // SteamUserStats()->ShowLeaderboardUI();
    /*SteamUserStats()->RequestUserStats(SteamUser()->GetSteamID());
    SteamUserStats()->FindOrCreateLeaderboard("Your_Leaderboard_Name", k_ELeaderboardSortMethodDescending, k_ELeaderboardDisplayTypeNumeric);
    SteamUserStats()->DownloadLeaderboardEntries(leaderboardHandle, k_ELeaderboardDataRequestGlobal, 1, 10);*/

}

// saves to cloud
unsigned char steam_remote_save(const char* save_name, unsigned char *buffer, int byte_length) {
    return SteamRemoteStorage()->FileWrite(save_name, buffer, byte_length);
}

unsigned char* steam_remote_read(const char* save_name, int* file_length) {
    *file_length = SteamRemoteStorage()->GetFileSize(save_name);
    unsigned char* file_content = (unsigned char*) malloc(*file_length);
    if (!SteamRemoteStorage()->FileRead(save_name, file_content, *file_length)) {
        free(file_content);
        return NULL;
    }
    return file_content;
}

void publish_to_workshop(const char* contentPath, const char* title, const char* description) {
    int workshopItemID = 0;
    SteamUGC()->CreateItem(SteamUtils()->GetAppID(), k_EWorkshopFileTypeCommunity);
    SteamUGC()->StartItemUpdate(SteamUtils()->GetAppID(), workshopItemID);
    SteamUGC()->SetItemTitle(workshopItemID, title);
    SteamUGC()->SetItemDescription(workshopItemID, description);
    SteamUGC()->SetItemContent(workshopItemID, contentPath);
    SteamUGC()->SubmitItemUpdate(workshopItemID, NULL);
}

void drop_trading_card(int cardID) {
    // SteamUser()->GetSteamID();
    // SteamUser()->AwardSteamAchievement("Your_Card_Achievement");
}

void enable_voice_chat() {
    // SteamFriends()->SetVoiceRecording(true);
    // SteamFriends()->SetInGameVoiceSpeaking(SteamUser()->GetSteamID(), true);
    // Implement the necessary voice chat handling.
}

const char* get_steam_user_name() {
    // Get the SteamID of the currently logged-in user
    CSteamID steamID = get_steam_id();
    // Fetch the user's name using the Steam Friends interface
    const char* userName = SteamFriends()->GetFriendPersonaName(steamID);
    // For demonstration purposes, let us display the name
    // std::cout << "Steam User Name: " << userName << std::endl;
    return userName;
}

int get_friends_count() {
    int flags = k_EFriendFlagImmediate; // k_EFriendFlagAll
    return SteamFriends()->GetFriendCount(flags);
}

uint64_t get_friend_id(int index) {
    int flags = k_EFriendFlagImmediate; // k_EFriendFlagAll
    CSteamID steamID = SteamFriends()->GetFriendByIndex(index, flags);
    return steamID.ConvertToUint64();
}

const char* get_friend_name(uint64_t steam_id) {
    CSteamID steam_id2 = CSteamID(static_cast<uint64>(steam_id));
    return SteamFriends()->GetFriendPersonaName(steam_id2);
}

const char* get_friend_nickname(uint64_t steam_id) {
    CSteamID steam_id2 = CSteamID(static_cast<uint64>(steam_id));
    return SteamFriends()->GetPlayerNickname(steam_id2);
}


// achievements

void steam_unlock_achievement(const char* achievement_name) {
    SteamUserStats()->SetAchievement(achievement_name);
    SteamUserStats()->StoreStats();
}
