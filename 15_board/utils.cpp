#include <cstdlib>

int mod(int a, unsigned n) {
    int mod = a % n;
    return mod < 0 ? mod + n : mod;
}

unsigned manh_distance_in_matrix(int a, int b, int n) {
    return abs(a % n - b % n) + abs((int)(a / n) - (int)(b / n));
}