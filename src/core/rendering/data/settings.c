unsigned char render_backend = zox_render_backend_opengl;
unsigned char is_using_vulkan = 0;
unsigned char is_render_fog = 1;
float3 fog_color = (float3) { 0.5f, 0.55f, 0.58f };
float fog_density = 0.1f; // 0326f;
// float3 viewport_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
float3 viewport_clear_color = (float3) { 0.0f, 0.0f, 0.0f };

float get_fog_density() {
    if (is_render_fog) return fog_density * fog_density;
    else return 0.0f;
}
