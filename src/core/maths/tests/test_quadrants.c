int test_quadrants() {
    float x1 = 0;
    float x2 = 90;
    float x3 = 180;
    float x4 = 270;
    float x5 = 360;
    float4 q1 = quaternion_from_euler((float3) { 0, x1 * degreesToRadians, 0 });
    float4 q2 = quaternion_from_euler((float3) { 0, x2 * degreesToRadians, 0 });
    float4 q3 = quaternion_from_euler((float3) { 0, x3 * degreesToRadians, 0 });
    float4 q4 = quaternion_from_euler((float3) { 0, x4 * degreesToRadians, 0 });
    float4 q5 = quaternion_from_euler((float3) { 0, x5 * degreesToRadians, 0 });
    float3 e2 = quaternion_to_euler(q2);
    float3 e3 = quaternion_to_euler(q3);
    float3 e4 = quaternion_to_euler(q4);
    zoxel_log(" > [%f] - [%fx%fx%f]:\n", x2, e2.x, e2.y, e2.z);
    test_quaternion_math(q2);
    zoxel_log(" > [%f] - [%fx%fx%f]:\n", x3, e3.x, e3.y, e3.z);
    test_quaternion_math(q3);
    zoxel_log(" > [%f] - [%fx%fx%f]:\n", x4, e4.x, e4.y, e4.z);
    test_quaternion_math(q4);
    int quadrant1 = quaternion_to_quadrant(q1);
    int quadrant2 = quaternion_to_quadrant(q2);
    int quadrant3 = quaternion_to_quadrant(q3);
    int quadrant4 = quaternion_to_quadrant(q4);
    int quadrant5 = quaternion_to_quadrant(q5);
    printf("Angle: %f, Quadrant: %i\n", x1, quadrant1);
    printf("Angle: %f, Quadrant: %i\n", x2, quadrant2);
    printf("Angle: %f, Quadrant: %i\n", x3, quadrant3);
    printf("Angle: %f, Quadrant: %i\n", x4, quadrant4);
    printf("Angle: %f, Quadrant: %i\n", x5, quadrant5);
    return 0;
}