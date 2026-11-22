#include "Josephus.h"

// 0-based index of the survivor in a circle of n people where counting starts
// at index 0 and the next skip value is pattern[round % m].
//
// Round r eliminates index e = (k-1) % n. The remaining n-1 people then start
// counting from the person after e, so new index j maps back to
// (e + 1 + j) % n in the circle of n.
static int survivorIndex(int n, int round, const int* pattern, int m) {
    if (n == 1) return 0;
    int k = pattern[round % m];
    int e = (k - 1) % n;
    return (e + 1 + survivorIndex(n - 1, round + 1, pattern, m)) % n;
}

int predictSurvivor(int n, int start, const int* pattern, int m) {
    return ((start - 1) + survivorIndex(n, 0, pattern, m)) % n + 1;
}
