//! Used to store vertex data.
/**
*   \todo Seperate mesh data into different files.
*/
typedef struct
{
    float3 *vertices;
    float3 *normals;
    float3 *colors;
    float2 *uvs;
} Mesh;