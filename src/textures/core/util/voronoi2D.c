// critical for finding voronoi index from a position
int get_closest_index(int2 point, int2 *points, int points_length, int2 size) {
    float2 point2 = (float2) { point.x, point.y };
    float smallestDistance = 100000; // float.MaxValue;
    float smallestIndex = 0;
    for (int i = 0; i < points_length; i++) {
        int2 otherPoint = points[i];
        float distance = float2_distance(point2, (float2) { otherPoint.x, otherPoint.y });
        float distance2 = float2_distance(point2, (float2) { otherPoint.x, otherPoint.y + size.y });
        float distance3 = float2_distance(point2, (float2) { otherPoint.x, otherPoint.y - size.y });
        float distance4 = float2_distance(point2, (float2) { otherPoint.x + size.x, otherPoint.y });
        float distance5 = float2_distance(point2, (float2) { otherPoint.x - size.x, otherPoint.y });
        if (distance < smallestDistance) {
            smallestDistance = distance;
            smallestIndex = i;
        }
        if (distance2 < smallestDistance) {
            smallestDistance = distance2;
            smallestIndex = i;
        }
        if (distance3 < smallestDistance) {
            smallestDistance = distance3;
            smallestIndex = i;
        }
        if (distance4 < smallestDistance) {
            smallestDistance = distance4;
            smallestIndex = i;
        }
        if (distance5 < smallestDistance) {
            smallestDistance = distance5;
            smallestIndex = i;
        }
    }
    return smallestIndex;
}


void voronoi2D(color *pixels, const int2 size, const color base_color, color variance, float darken) {
    int pixels_length = size.x * size.y;
    int points_length = size.x; // 16;
    float pointCloseness = size.x / 5; //3;
    int2 points[points_length];
    color regionColors[points_length];
    byte is_darken[pixels_length];
    for (int i = 0; i < points_length; i++) {
        points[i] = int2_zero;
        regionColors[i] = color_white;
        int2 newPoint = (int2) { rand() % size.x, rand() % size.y };
        int count = 0;
        while (count <= 128) {
            newPoint = (int2) { rand() % size.x, rand() % size.y };
            byte isTooClose = 0;
            for (int j = i - 1; j >= 0; j--) {
                int2 otherPoint = points[j];
                if (    newPoint.x + pointCloseness > otherPoint.x - pointCloseness &&
                        newPoint.x - pointCloseness < otherPoint.x + pointCloseness &&
                        newPoint.y + pointCloseness > otherPoint.y - pointCloseness &&
                        newPoint.y - pointCloseness < otherPoint.y + pointCloseness)
                {
                    isTooClose = 1;
                    break;
                }
            }
            if (!isTooClose) break;
            count++;
        }
        points[i] = newPoint;
        byte r = (byte)(base_color.r + (variance.r ? rand() % variance.r : 0));
        byte g = (byte)(base_color.g + (variance.r ? rand() % variance.g : 0));
        byte b = (byte)(base_color.b + (variance.r ? rand() % variance.b : 0));
        regionColors[i] = (color) { r, g, b, 255 };

        // zox_log("region color [%i] %ix%ix%i\n", i, r, g, b)
    }
    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            int pixelIndex = (int) y * size.x + (int) x;
            int regionIndex = get_closest_index((int2) { x, y }, points, points_length, size);
            pixels[pixelIndex] = regionColors[regionIndex];
        }
    }
    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            int pixelIndex = (int) y * size.x + (int) x;
            color pixel = pixels[pixelIndex];
            int2 positionUp = (int2) { x, y + 1 };
            if (positionUp.y == size.y) positionUp.y = 0;
            int2 positionRight = (int2) { x + 1, y };
            if (positionRight.x == size.x) positionRight.x = 0;
            int pixelIndexUp = (int) (positionUp.y) * size.x + (int)(positionUp.x);
            int pixelIndexRight = (int) (positionRight.y) * size.x + (int)(positionRight.x);
            byte colorDiffUp = !color_equal(pixel, pixels[pixelIndexUp]);
            byte colorDiffRight = !color_equal(pixel, pixels[pixelIndexRight]);
            if (colorDiffUp || colorDiffRight) is_darken[pixelIndex] = 1;
            else is_darken[pixelIndex] = 0;
        }
    }
    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            int pixelIndex = (int)y * size.x + (int)x;
            if (is_darken[pixelIndex]) {
                int r = (int) pixels[pixelIndex].r;
                int g = (int) pixels[pixelIndex].g;
                int b = (int) pixels[pixelIndex].b;
                r = ((int)(r * darken));
                g = ((int)(g * darken));
                b = ((int)(b * darken));
                pixels[pixelIndex] = (color) { (byte) r, (byte)g, (byte)b, 255 };
            }
        }
    }
}
