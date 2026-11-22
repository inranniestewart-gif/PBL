#include "UndoStack.h"

UndoStack::UndoStack() : topNode(nullptr), count(0) {}

UndoStack::~UndoStack() { clear(); }

void UndoStack::push(const StepRecord& r) {
    topNode = new StackNode(r, topNode);
    count++;
}

bool UndoStack::pop(StepRecord& out) {
    if (!topNode) return false;
    StackNode* t = topNode;
    out = t->rec;
    topNode = t->next;
    delete t;
    count--;
    return true;
}

bool UndoStack::peek(StepRecord& out) const {
    if (!topNode) return false;
    out = topNode->rec;
    return true;
}

bool UndoStack::empty() const { return topNode == nullptr; }

void UndoStack::clear() {
    while (topNode) {
        StackNode* t = topNode;
        topNode = t->next;
        delete t;
    }
    count = 0;
}

int UndoStack::size() const { return count; }
