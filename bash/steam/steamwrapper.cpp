// g++ -shared -o lib/libsteam_wrapper.so steam_wrapper.cpp -Iinclude/steam -Llib -lsteam_api
#include "../../include/steam/steam_api.h"
#include "steamwrapper.c"
#include <iostream>  // For demonstration purposes

unsigned char initialize_steam() {
    return SteamAPI_Init();
}

void shutdown_steam() {
    SteamAPI_Shutdown();
}

void authenticate_user() {
    // SteamUser()->LogOn(new CSteamID(), k_EAccountTypeIndividual);
    // Handle the callbacks to check when authentication is complete.
}

void show_leaderboard() {
    // SteamUserStats()->RequestCurrentStats();
    // SteamUserStats()->ShowLeaderboardUI();
    /*SteamUserStats()->RequestUserStats(SteamUser()->GetSteamID());
    SteamUserStats()->FindOrCreateLeaderboard("Your_Leaderboard_Name", k_ELeaderboardSortMethodDescending, k_ELeaderboardDisplayTypeNumeric);
    SteamUserStats()->DownloadLeaderboardEntries(leaderboardHandle, k_ELeaderboardDataRequestGlobal, 1, 10);*/

}

void unlock_achievement(const char* achievementID) {
    SteamUserStats()->SetAchievement(achievementID);
    SteamUserStats()->StoreStats();
}

void save_to_cloud() {
    // SteamRemoteStorage()->FileWrite("SaveGame", game_data, sizeof(GameData));
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

CSteamID get_steam_id() {
    CSteamID steamID = SteamUser()->GetSteamID();
    return steamID;
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

uint64 get_friend_id(int index) {
    int flags = k_EFriendFlagImmediate; // k_EFriendFlagAll
    CSteamID steamID = SteamFriends()->GetFriendByIndex(index, flags);
    return steamID.ConvertToUint64();
}

const char* get_friend_name(uint64 steam_id) {
    CSteamID steam_id2 = CSteamID(steam_id);
    return SteamFriends()->GetFriendPersonaName(steam_id2);
}
