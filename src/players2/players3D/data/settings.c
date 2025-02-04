const unsigned char zox_players_reverse_x = 0;
const unsigned char zox_players_reverse_y = 0;
const unsigned char zox_players_reverse_rotate_x = 0;
const unsigned char zox_players_reverse_rotate_y = 0;
const double gamepad_rotate_multiplier_x = 0.04;
const double gamepad_rotate_multiplier_y = 0.03;
const double mouse_rotate_multiplier = 0.0032; // 0.008;
const float touchscreen_rotate_multiplier = 0.6f;
const float min_mouse_delta3 = 0.01f;
const float min_mouse_delta2 = 24.0f;
const float max_mouse_delta3 = 60.0f;
const float max_mouse_delta4 = 120.0f;
const float max_mouse_delta2 = 200.0f;
const double max_rotate_speed = 0.2; //  0.23;
#define disable_player_rotate_alpha_force
// shit remove this atm, it doubles up for coop
const double run_speed = 1.8;
const double run_accceleration = 2.2;
const float backwards_multiplier = 0.8f;
const float2 player_movement_power = { 17, 19 };
const float2 max_velocity = { 1.24f, 1.4f }; // 60 * 60, 160 * 60 };
// #define zox_debug_player_speed_limits
#define player_vox_scale  (1 / 64.0f) * 1.6f
char* player_vox_model = "tall_cube";
