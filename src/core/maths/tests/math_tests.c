void run_math_tests() {
    float4 leftRotation = quaternion_from_euler( (float3) { 0 * degreesToRadians, 90 * degreesToRadians, 0 * degreesToRadians });
    float4 rightRotation = quaternion_from_euler( (float3) { 0 * degreesToRadians, -90 * degreesToRadians, 0 * degreesToRadians });
    float4 downRotation = quaternion_from_euler( (float3) { 90 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
    float4 upRotation = quaternion_from_euler( (float3) { -90 * degreesToRadians, 0 * degreesToRadians, 0 * degreesToRadians });
    float4 leftDownRotation = quaternion_from_euler( (float3) { 90 * degreesToRadians, 90 * degreesToRadians, 0 * degreesToRadians });
    float4 rightUpRotation = quaternion_from_euler( (float3) { -90 * degreesToRadians, -90 * degreesToRadians, 0 * degreesToRadians });
    printf("Testing [quaternion_rotate] v1\n");
    float4 rotation = float4_identity;
    print_float4(rotation);
    rotation = quaternion_rotate(leftRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(rightRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(rightRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(leftRotation, rotation);
    print_float4(rotation);
    printf("End Testing [quaternion_rotate] v1\n");
    printf("Testing [quaternion_rotate] v2\n");
    rotation = float4_identity;
    print_float4(rotation);
    rotation = quaternion_rotate(downRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(leftRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(rightRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(upRotation, rotation);
    print_float4(rotation);
    printf("End Testing [quaternion_rotate] v2\n");
    printf("Testing [quaternion_rotate] v3\n");
    rotation = float4_identity;
    print_float4(rotation);
    rotation = quaternion_rotate(leftDownRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(rightUpRotation, rotation);
    print_float4(rotation);
    printf("End Testing [quaternion_rotate] v3\n");
    printf("Testing [quaternion_rotate] v4\n");
    rotation = float4_identity;
    print_float4(rotation);
    rotation = quaternion_rotate(leftRotation, rotation);
    rotation = quaternion_rotate(downRotation, rotation);
    print_float4(rotation);
    rotation = quaternion_rotate(upRotation, rotation);
    rotation = quaternion_rotate(rightRotation, rotation);
    print_float4(rotation);
    printf("End Testing [quaternion_rotate] v4\n");

    printf("Testing [float4_rotate_float3]\n");
    float3 forward = { 0, 0, 1 };
    float3_print(forward);
    forward = float4_rotate_float3(leftRotation, forward);
    float3_print(forward);
    forward = float4_rotate_float3(rightRotation, forward);
    float3_print(forward);
    forward = float4_rotate_float3(rightRotation, forward);
    float3_print(forward);
    forward = float4_rotate_float3(leftRotation, forward);
    float3_print(forward);
    printf("End Testing [float4_rotate_float3]\n");

    printf("Testing [quaternion_to_euler]\n");
    float3 leftRotation0 = { 0 * degreesToRadians, 90 * degreesToRadians, 0 * degreesToRadians };
    float3_print(leftRotation0);
    print_float4(leftRotation);
    float3 leftRotation2 = quaternion_to_euler(leftRotation);
    float3_print(leftRotation2);
    float4 leftRotation3 = quaternion_from_euler(leftRotation2);
    print_float4(leftRotation3);
    printf("End Testing [quaternion_to_euler]\n");
}