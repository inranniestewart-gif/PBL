#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() : heap(new Candidate[16]), count(0), capacity(16) {}

PriorityQueue::~PriorityQueue() { delete[] heap; }

bool PriorityQueue::lessThan(const Candidate& a, const Candidate& b) {
    if (a.weight != b.weight) return a.weight < b.weight;
    return a.order < b.order;
}

void PriorityQueue::grow() {
    int newCap = capacity * 2;
    Candidate* bigger = new Candidate[newCap];
    for (int i = 0; i < count; i++) bigger[i] = heap[i];
    delete[] heap;
    heap = bigger;
    capacity = newCap;
}

void PriorityQueue::siftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (!lessThan(heap[i], heap[parent])) break;
        Candidate t = heap[i];
        heap[i] = heap[parent];
        heap[parent] = t;
        i = parent;
    }
}

void PriorityQueue::siftDown(int i) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
        if (l < count && lessThan(heap[l], heap[smallest])) smallest = l;
        if (r < count && lessThan(heap[r], heap[smallest])) smallest = r;
        if (smallest == i) break;
        Candidate t = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = t;
        i = smallest;
    }
}

void PriorityQueue::push(const Candidate& c) {
    if (count == capacity) grow();
    heap[count] = c;
    siftUp(count);
    count++;
}

bool PriorityQueue::pop(Candidate& out) {
    if (count == 0) return false;
    out = heap[0];
    count--;
    if (count > 0) {
        heap[0] = heap[count];
        siftDown(0);
    }
    return true;
}

bool PriorityQueue::empty() const { return count == 0; }
int PriorityQueue::size() const { return count; }
void PriorityQueue::clear() { count = 0; }
