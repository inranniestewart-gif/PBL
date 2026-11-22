# Lastone - Fair Elimination Engine (Phase III)

C++ console game for TCS 302 (Data Structures with C) and TCS 307 (OOP with C++).
Team DSCPP-III-2026-T343: Himanshu Kumar (lead), Rannie Stewart. Mentor: Ms. Isha Deshmukh.

## Build

    cl /EHsc /Zi main.cpp CircularList.cpp EliminationEngine.cpp SkipQueue.cpp UndoStack.cpp PriorityQueue.cpp Josephus.cpp

Tests (separate executable, run from the project root):

    cl /EHsc /Zi /Fe:tests\test_phase3.exe tests\test_phase3.cpp CircularList.cpp EliminationEngine.cpp SkipQueue.cpp UndoStack.cpp PriorityQueue.cpp Josephus.cpp
    tests\test_phase3.exe

## Files

| File | Purpose |
|---|---|
| Player.h | Player record: id, name, weight, immunity tokens |
| CircularList | Circular singly linked list (tail pointer). Adds `insertAfter` and `findById` for undo |
| SkipQueue | Rotating queue of skip values. Adds `undo()` to reverse one rotation |
| EliminationEngine | k-step traversal, removal, ring reconnection, undo/redo, fairness mode, immunity |
| UndoStack | Hand-built linked-list stack of `StepRecord`, used for both undo and redo |
| PriorityQueue | Hand-built binary min-heap of `Candidate`, used by fairness mode |
| Josephus | Recursive survivor check for classic mode |
| main.cpp | Console UI |

## Phase III features

**Undo / redo (stack).** Every step pushes a `StepRecord` (removed player, the node it followed,
whether it was the tail, engine `prev`/`cur` ids before the step, round number). Undo pops it,
reinserts the player, restores `prev`/`cur`, the round counter and the skip rotation, and pushes
the record onto the redo stack. Redo replays the step (the engine is deterministic). A new step
clears the redo stack. Records store player ids, not `Node*`, because a reinserted node has a new
address. Works after the game has finished.

**Recursive survivor check.** `survivorIndex(n, round, pattern, m)` eliminates index `(k-1) % n`,
then recurses on `n-1` people starting after it: `f(n,r) = (e + 1 + f(n-1, r+1)) % n`, `f(1,r) = 0`.
Shown before the game starts and compared with the engine's survivor at the end (PASS / MISMATCH).
Only offered in classic mode with no immunity tokens, because those change the rules it models.

**Priority-queue fairness mode.** The skip still picks a landing spot. The next `window` players
(landing spot included) go into a min-heap keyed on (weight, distance from landing spot) and the
heap's minimum is eliminated, so heavier players are protected. Equal weights always eliminate the
landing spot, so fairness mode with equal weights is identical to classic mode (tested). Counting
resumes after the victim.

**Immunity tokens.** When a player is chosen as victim and has a token, one token is spent, nobody
is eliminated that round, and counting resumes after that player. Undo gives the token back.
Works in both modes.

## Menu

1 Step, 2 Run to end, 3 Show ring, 4 Undo, 5 Redo, 0 Quit. The program no longer exits on its
own when the game ends, so undo stays available; quit with 0.

## Tests (v0.1, 2372 checks)

- 1555 classic cases (exhaustive sweep n=2-12, every start, k=1-15, plus 400 random multi-skip patterns) against an independent vector simulation and the recursive check
- 150 full undo-all / redo-all cycles checking the ring after every step
- Edge cases: empty stacks, redo cleared by a new step, skip rotation, head and tail removal, undo after finish
- Fairness: equal weights equal classic (200 cases), hand-computed example (weights 5,1,3,2,4 window 3: out 2,4,3,5, survivor 1), undo/redo with random weights
- Immunity: token spent and restored, termination, full undo restores ring and tokens (100 cases)

Also run clean under AddressSanitizer and UndefinedBehaviorSanitizer (no leaks, no invalid access) with g++.

## Known notes

- Compiled and tested with g++ 13 (-std=c++11 -Wall -Wextra). Not built with cl.exe in this environment; the code uses only C++11 features available in MSVC 2015 (vc140).
- Immunity tokens and weights are set from the console before the game; Himanshu's token work should be reconciled with `Player::immunity` and the check in `EliminationEngine::performStep`.
