#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "Player.h"

// Everything needed to reverse (and replay) one engine step.
// Players are referenced by id, never by Node*, because a reinserted node
// gets a new address.
struct StepRecord {
    bool eliminated;     // false = target was spared by an immunity token
    Player removed;      // eliminated: the removed player (copy)
    int protectedId;     // spared: id of the player whose token was spent
    int prevTargetId;    // eliminated: id of the node the victim followed
    bool wasTail;        // eliminated: victim was ring.tail() when removed
    int prevStateId;     // engine prev (by id) BEFORE the step
    int curStateId;      // engine cur  (by id) BEFORE the step
    int round;           // round number this step produced

    StepRecord()
        : eliminated(true), removed(), protectedId(0), prevTargetId(0),
          wasTail(false), prevStateId(0), curStateId(0), round(0) {}
};

// Hand-built singly linked-list stack of StepRecord.
class UndoStack {
    struct StackNode {
        StepRecord rec;
        StackNode* next;
        StackNode(const StepRecord& r, StackNode* n) : rec(r), next(n) {}
    };

    StackNode* topNode;
    int count;

    UndoStack(const UndoStack&);              // not copyable
    UndoStack& operator=(const UndoStack&);

public:
    UndoStack();
    ~UndoStack();

    void push(const StepRecord& r);
    bool pop(StepRecord& out);    // false when empty
    bool peek(StepRecord& out) const;
    bool empty() const;
    void clear();
    int size() const;
};

#endif
