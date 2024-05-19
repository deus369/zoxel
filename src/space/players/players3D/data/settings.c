const unsigned char zox_players_reverse_x = 0;
const unsigned char zox_players_reverse_y = 0;
const unsigned char zox_players_reverse_rotate_x = 0;
const unsigned char zox_players_reverse_rotate_y = 0;
const double movement_power_x = 4;
const double movement_power_z = 5;
const double gamepad_rotate_multiplier_x = 0.04;
const double gamepad_rotate_multiplier_y = 0.03;
const double mouse_rotate_multiplier = 0.0032; // 0.008;
const float min_mouse_delta3 = 0.01f;
const float min_mouse_delta2 = 24.0f;
const float max_mouse_delta3 = 60.0f;
const float max_mouse_delta4 = 120.0f;
const float max_mouse_delta2 = 200.0f;
const double max_rotate_speed = 0.2; //  0.23;
#define disable_player_rotate_alpha_force
// shit remove this atm, it doubles up for coop
// float3 player_euler = (float3) { 0, 0, 0 };
// float3 camera_euler = (float3) { 0, 180 * degreesToRadians, 0 };
