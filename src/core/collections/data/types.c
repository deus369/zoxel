typedef unsigned int uint;
typedef unsigned char byte;

typedef struct {
    byte x, y;
} byte2;

typedef struct {
    byte x, y, z;
} byte3;

typedef struct {
    byte x, y, z, w;
} byte4;

typedef struct {
    int x, y;
} int2;

typedef struct {
    int x, y, z;
} int3;

typedef struct {
    int x, y, z, w;
} int4;

typedef struct {
    uint32_t x, y;
} uint2;

typedef struct {
    uint32_t x, y, z;
} uint3;

typedef struct {
    float x, y;
} float2;

typedef struct {
    float x, y, z;
} float3;

typedef struct {
    float x, y, z, w;
} float4;

typedef struct {
    float x, y, z, w, u, v;
} float6;

typedef struct {
    float3 x, y, z;
} float3x3;

typedef struct {
    float4 x, y, z, w;
} float4x4;

typedef struct {
    double x, y;
} double2;

typedef struct {
    double x, y, z;
} double3;

typedef struct {
    double x, y, z, w;
} double4;

typedef struct {
    byte r, g, b, a;
} color;

typedef struct {
    byte r, g, b;
} color_rgb;