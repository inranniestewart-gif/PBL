#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "Player.h"


struct StepRecord {
    bool eliminated;     
    Player removed;     
    int protectedId;    
    int prevTargetId;    
    bool wasTail;        
    int prevStateId;     
    int curStateId;     
    int round;          

    StepRecord()
        : eliminated(true), removed(), protectedId(0), prevTargetId(0),
          wasTail(false), prevStateId(0), curStateId(0), round(0) {}
};


class UndoStack {
    struct StackNode {
        StepRecord rec;
        StackNode* next;
        StackNode(const StepRecord& r, StackNode* n) : rec(r), next(n) {}
    };

    StackNode* topNode;
    int count;

    UndoStack(const UndoStack&);             
    UndoStack& operator=(const UndoStack&);

public:
    UndoStack();
    ~UndoStack();

    void push(const StepRecord& r);
    bool pop(StepRecord& out);   
    bool peek(StepRecord& out) const;
    bool empty() const;
    void clear();
    int size() const;
};

#endif
