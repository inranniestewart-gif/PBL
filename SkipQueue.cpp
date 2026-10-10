
#include "SkipQueue.h"

void SkipQueue::add(int k) { q.push(k); }

int SkipQueue::next() {
    int k = q.front();
    q.pop();
    q.push(k);
    return k;
}
