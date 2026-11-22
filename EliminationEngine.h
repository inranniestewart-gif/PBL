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
    int window;            
    UndoStack undoStack;
    UndoStack redoStack;

    void performStep(bool clearRedo);

public:
   
    EliminationEngine(CircularList& ring, SkipQueue& skips, int startPosition, int windowSize = 1);

    bool finished();
    void step();
    void run();

    bool undo();          
    bool redo();           
    bool canUndo() const;
    bool canRedo() const;
    int currentRound() const;
};

#endif
