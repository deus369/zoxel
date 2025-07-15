#include <unistd.h>
#include <time.h>

// Robert Jenkins' 96 bit Mix Function
/*unsigned long mix(unsigned long a, unsigned long b, unsigned long c) {
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

unsigned long get_unique_time_seed() {
    clock_t clk = clock();
    time_t t = time(NULL);
    unsigned long pid = (unsigned long)getpid();
    return mix((unsigned long)clk, (unsigned long)t, pid);
}*/

/*unsigned long get_unique_time_seed() {
    return mix(clock(), time(NULL), getpid());
}*/

uint32_t mix(uint32_t a, uint32_t b, uint32_t c) {
    a = a - b;  a = a - c;  a = a ^ (c >> 13);
    b = b - c;  b = b - a;  b = b ^ (a << 8);
    c = c - a;  c = c - b;  c = c ^ (b >> 13);
    a = a - b;  a = a - c;  a = a ^ (c >> 12);
    b = b - c;  b = b - a;  b = b ^ (a << 16);
    c = c - a;  c = c - b;  c = c ^ (b >> 5);
    a = a - b;  a = a - c;  a = a ^ (c >> 3);
    b = b - c;  b = b - a;  b = b ^ (a << 10);
    c = c - a;  c = c - b;  c = c ^ (b >> 15);
    return c;
}

uint32_t get_unique_time_seed() {
    clock_t clk = clock();
    time_t t = time(NULL);
    uint32_t pid = (uint32_t)getpid();

    return mix((uint32_t)clk, (uint32_t)t, pid);
}
