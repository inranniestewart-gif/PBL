
#ifndef ELIMINATIONENGINE_H
#define ELIMINATIONENGINE_H

#include "CircularList.h"
#include "SkipQueue.h"

class EliminationEngine {
    CircularList& ring;
    SkipQueue& skips;
    Node* prev;     
    Node* cur;     
    int round;

public:
    EliminationEngine(CircularList& ring, SkipQueue& skips, int startPosition);

    bool finished();   
    void step();        
    void run();         
};

#endif
