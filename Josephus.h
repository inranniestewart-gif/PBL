#ifndef JOSEPHUS_H
#define JOSEPHUS_H

// Recursive survivor check for the classic mode (no weights, no immunity).
// pattern[0..m-1] is the skip pattern in the order it was entered; round r
// uses pattern[r % m]. Returns the survivor's position (= player id, since
// players are numbered 1..n in ring order). start is 1-based.
int predictSurvivor(int n, int start, const int* pattern, int m);

#endif
