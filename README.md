air Selection Engine (Phase II)

A configurable console application in C++ that simulates circular elimination (the Josephus problem). Participants stand in a ring, the engine counts forward by a skip value, removes the selected participant, reconnects the ring, and repeats until one survivor remains.

Team ID: DSCPP-III-2026-T343 | Graphic Era (Deemed to be University), Dehradun | Session 2026-27

Features (Phase II)
Configurable number of participants (2 to 1000)
Configurable starting position
Configurable skip pattern that repeats in a cycle (for example 2, 3, 2, 3)
Step-by-step or run-to-end play, with the ring viewable at any time
Input validation on every prompt
Project Structure
File	Purpose	Owner
main.cpp	Console UI and input validation	Himanshu Kumar
Player.h	Participant class (constructor, destructor, overloaded == and <<)	Himanshu Kumar
CircularList.h / .cpp	Circular linked list that models the ring	Himanshu Kumar
SkipQueue.h / .cpp	Queue that cycles through the skip pattern	Himanshu Kumar
EliminationEngine.h / .cpp	Elimination rounds, node removal, ring reconnection	Siyavuya Rannie Stewart
Makefile	Build script	Team
Build and Run

Requires a C++11 compiler (g++).

make
./engine

Without make: g++ -std=c++11 *.cpp -o engine

On Windows (MinGW): g++ -std=c++11 *.cpp -o engine.exe, then engine.exe

Example

Input: 7 participants, start position 1, one skip value of 3, then choose 2 (run to end).

Round 1 (skip 3): Player3 (id 3) eliminated
Round 2 (skip 3): Player6 (id 6) eliminated
Round 3 (skip 3): Player2 (id 2) eliminated
Round 4 (skip 3): Player7 (id 7) eliminated
Round 5 (skip 3): Player5 (id 5) eliminated
Round 6 (skip 3): Player1 (id 1) eliminated

Final survivor: Player4 (id 4)
How It Works
main.cpp reads the settings and builds the ring with CircularList.
EliminationEngine moves to the starting position.
Each round it takes the next value from SkipQueue, moves that many participants forward, removes the selected one, and continues from the next participant.
When one participant remains, the survivor is printed.
Planned for Phase III
Stack-based undo and history replay
Priority-queue fairness mode
Immunity tokens and participant weights
Recursive survivor verification
