#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "CircularList.h"

// One candidate for elimination in fairness mode.
struct Candidate {
    int weight;     // lower weight is eliminated first
    int order;      // distance from the landing spot (0 = landed player); breaks ties
    Node* before;   // node that precedes this candidate in the ring
    Node* node;     // the candidate itself
};

// Hand-built binary min-heap on (weight, order).
class PriorityQueue {
    Candidate* heap;
    int count;
    int capacity;

    PriorityQueue(const PriorityQueue&);              // not copyable
    PriorityQueue& operator=(const PriorityQueue&);

    static bool lessThan(const Candidate& a, const Candidate& b);
    void siftUp(int i);
    void siftDown(int i);
    void grow();

public:
    PriorityQueue();
    ~PriorityQueue();

    void push(const Candidate& c);
    bool pop(Candidate& out);    // removes the minimum; false when empty
    bool empty() const;
    int size() const;
    void clear();
};

#endif
