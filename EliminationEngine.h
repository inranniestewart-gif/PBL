#ifndef ELIMINATIONENGINE_H
#define ELIMINATIONENGINE_H

#include "CircularList.h"
#include "SkipQueue.h"
#include "UndoStack.h"

class EliminationEngine {
    CircularList& ring;
    SkipQueue& skips;
    Node* prev;
    Node* cur;
    int round;
    int window;            // 1 = classic; >1 = fairness mode candidate window
    UndoStack undoStack;
    UndoStack redoStack;

    void performStep(bool clearRedo);

public:
    // windowSize 1 keeps the classic rules. windowSize > 1 enables fairness
    // mode: the skip picks a landing spot, then the lowest-weight player among
    // the next windowSize players (landing spot included) is the victim.
    EliminationEngine(CircularList& ring, SkipQueue& skips, int startPosition, int windowSize = 1);

    bool finished();
    void step();
    void run();

    bool undo();           // false when there is nothing to undo
    bool redo();           // false when there is nothing to redo
    bool canUndo() const;
    bool canRedo() const;
    int currentRound() const;
};

#endif
