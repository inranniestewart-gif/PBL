#include "EliminationEngine.h"
#include "PriorityQueue.h"

EliminationEngine::EliminationEngine(CircularList& r, SkipQueue& s, int startPosition, int windowSize)
    : ring(r), skips(s), round(0), window(windowSize < 1 ? 1 : windowSize) {
    prev = ring.tail();
    cur = ring.head();
    for (int i = 1; i < startPosition; i++) {
        prev = cur;
        cur = cur->next;
    }
}

bool EliminationEngine::finished() { return ring.size() == 1; }

void EliminationEngine::performStep(bool clearRedo) {
    if (finished()) return;

    StepRecord rec;
    rec.prevStateId = prev->player.id;
    rec.curStateId = cur->player.id;

    int k = skips.next();
    for (int i = 1; i < k; i++) {
        prev = cur;
        cur = cur->next;
    }

    // prev/cur now sit on the landing spot. Pick the victim.
    Node* landed = cur;
    Node* victimBefore = prev;
    Node* victim = cur;

    if (window > 1) {
        int w = window < ring.size() ? window : ring.size();
        PriorityQueue pq;
        Node* before = prev;
        Node* node = cur;
        for (int i = 0; i < w; i++) {
            Candidate c;
            c.weight = node->player.weight;
            c.order = i;
            c.before = before;
            c.node = node;
            pq.push(c);
            before = node;
            node = node->next;
        }
        Candidate best;
        pq.pop(best);
        victim = best.node;
        victimBefore = best.before;
    }

    round++;
    rec.round = round;

    if (victim->player.immunity > 0) {
        // Spared: spend one token, counting resumes after the victim.
        victim->player.immunity--;
        rec.eliminated = false;
        rec.protectedId = victim->player.id;
        cout << "Round " << round << " (skip " << k << "): " << victim->player
             << " protected by immunity (" << victim->player.immunity << " left)\n";
        prev = victim;
        cur = victim->next;
    } else {
        rec.eliminated = true;
        rec.removed = victim->player;
        rec.prevTargetId = victimBefore->player.id;
        rec.wasTail = (victim == ring.tail());

        cout << "Round " << round << " (skip " << k << "): " << victim->player << " eliminated";
        if (victim != landed)
            cout << " [landed on " << landed->player << ", lowest weight in window]";
        cout << "\n";

        ring.removeAfter(victimBefore);
        prev = victimBefore;
        cur = prev->next;
    }

    undoStack.push(rec);
    if (clearRedo) redoStack.clear();
}

void EliminationEngine::step() { performStep(true); }

void EliminationEngine::run() {
    while (!finished()) step();
}

bool EliminationEngine::undo() {
    StepRecord rec;
    if (!undoStack.pop(rec)) return false;

    if (rec.eliminated) {
        Node* before = ring.findById(rec.prevTargetId);
        ring.insertAfter(before, rec.removed, rec.wasTail);
        cout << "Undid round " << rec.round << ": " << rec.removed << " reinstated\n";
    } else {
        Node* n = ring.findById(rec.protectedId);
        n->player.immunity++;
        cout << "Undid round " << rec.round << ": " << n->player
             << " immunity token restored\n";
    }

    // Both nodes were in the ring before the step, so they exist again now.
    prev = ring.findById(rec.prevStateId);
    cur = ring.findById(rec.curStateId);
    round = rec.round - 1;
    skips.undo();

    redoStack.push(rec);
    return true;
}

bool EliminationEngine::redo() {
    StepRecord rec;
    if (!redoStack.pop(rec)) return false;
    // The engine is deterministic, so replaying the step reproduces the record.
    performStep(false);
    return true;
}

bool EliminationEngine::canUndo() const { return !undoStack.empty(); }
bool EliminationEngine::canRedo() const { return !redoStack.empty(); }
int EliminationEngine::currentRound() const { return round; }

