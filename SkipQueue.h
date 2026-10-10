
#ifndef SKIPQUEUE_H
#define SKIPQUEUE_H

#include <queue>
using namespace std;

class SkipQueue {
    queue<int> q;

public:
    void add(int k);
    int next();    
};

#endif
