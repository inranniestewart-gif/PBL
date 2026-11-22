#include "SkipQueue.h"

void SkipQueue::add(int k) { q.push(k); }

int SkipQueue::next() {
    int k = q.front();
    q.pop();
    q.push(k);
    return k;
}

void SkipQueue::undo() {
   
    for (size_t i = 1; i < q.size(); i++) {
        int k = q.front();
        q.pop();
        q.push(k);
    }
}
