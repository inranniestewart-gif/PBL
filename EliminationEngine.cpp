
#include "EliminationEngine.h"

EliminationEngine::EliminationEngine(CircularList& r, SkipQueue& s, int startPosition)
    : ring(r), skips(s), round(0) {
    prev = ring.tail();
    cur = ring.head();
    for (int i = 1; i < startPosition; i++) {  
        prev = cur;
        cur = cur->next;
    }
}

bool EliminationEngine::finished() { return ring.size() == 1; }

void EliminationEngine::step() {
    if (finished()) return;

    int k = skips.next();
    for (int i = 1; i < k; i++) {               
        prev = cur;
        cur = cur->next;
    }

    round++;
    cout << "Round " << round << " (skip " << k << "): " << cur->player << " eliminated\n";

    ring.removeAfter(prev);                     
    cur = prev->next;                           
}

void EliminationEngine::run() {
    while (!finished()) step();
}
