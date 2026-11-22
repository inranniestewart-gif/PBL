#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "CircularList.h"


struct Candidate {
    int weight;     
    int order;      
    Node* before;   
    Node* node;     
};

.
class PriorityQueue {
    Candidate* heap;
    int count;
    int capacity;

    PriorityQueue(const PriorityQueue&);             
    PriorityQueue& operator=(const PriorityQueue&);

    static bool lessThan(const Candidate& a, const Candidate& b);
    void siftUp(int i);
    void siftDown(int i);
    void grow();

public:
    PriorityQueue();
    ~PriorityQueue();

    void push(const Candidate& c);
    bool pop(Candidate& out);   
    bool empty() const;
    int size() const;
    void clear();
};

#endif
