#include "Josephus.h"


static int survivorIndex(int n, int round, const int* pattern, int m) {
    if (n == 1) return 0;
    int k = pattern[round % m];
    int e = (k - 1) % n;
    return (e + 1 + survivorIndex(n - 1, round + 1, pattern, m)) % n;
}

int predictSurvivor(int n, int start, const int* pattern, int m) {
    return ((start - 1) + survivorIndex(n, 0, pattern, m)) % n + 1;
}
