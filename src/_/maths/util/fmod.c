// DIY fmod replacement (simple, maybe not as optimized)
double zox_fmod(double x, double y) {
    if (y == 0.0) return 0.0; // or handle error
    double div = x / y;
    double intpart = (double)(long long)div; // truncate towards zero
    return x - intpart * y;
}