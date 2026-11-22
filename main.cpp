#include <iostream>
#include <cstdlib>
#include <string>
#include "Player.h"
#include "CircularList.h"
#include "SkipQueue.h"
#include "EliminationEngine.h"
#include "Josephus.h"
using namespace std;


int readInt(const string& msg, int lo, int hi) {
    int x;
    while (true) {
        cout << msg;
        if (cin >> x && x >= lo && x <= hi) return x;
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter a number between " << lo << " and " << hi << "\n";
    }
}

static void printSurvivor(CircularList& ring, bool canVerify, int predicted) {
    int id = ring.head()->player.id;
    cout << "\nFinal survivor: " << ring.head()->player << "\n";
    if (canVerify) {
        if (id == predicted)
            cout << "Recursive check: survivor " << predicted << " matches (PASS)\n";
        else
            cout << "Recursive check: expected survivor " << predicted << " (MISMATCH)\n";
    }
}

int main() {
    int n = readInt("Number of participants (2-1000): ", 2, 1000);
    int start = readInt("Starting position (1-n): ", 1, n);
    int m = readInt("How many skip values in the pattern: ", 1, 20);

    SkipQueue skips;
    int pattern[20];
    for (int i = 1; i <= m; i++) {
        pattern[i - 1] = readInt("Skip value " + to_string(i) + ": ", 1, 1000);
        skips.add(pattern[i - 1]);
    }

    CircularList ring;
    for (int i = 1; i <= n; i++)
        ring.add(Player(i, "Player" + to_string(i)));

    int window = 1;
    bool anyImmunity = false;
    if (readInt("Advanced options - fairness mode / immunity tokens (1 yes, 0 no): ", 0, 1) == 1) {
        if (readInt("Fairness mode (1 yes, 0 no): ", 0, 1) == 1)
            window = readInt("Candidate window size (2-n): ", 2, n);

        while (true) {
            cout << "\nSetup: 1 Set weight  2 Give immunity tokens  0 Done\n";
            int s = readInt("Choice: ", 0, 2);
            if (s == 0) break;
            int id = readInt("Player id (1-n): ", 1, n);
            Node* node = ring.findById(id);
            if (s == 1) {
                node->player.weight = readInt("Weight (1-100, higher = safer): ", 1, 100);
                if (window == 1)
                    cout << "Note: weights only matter in fairness mode\n";
            } else {
                node->player.immunity = readInt("Immunity tokens (0-10): ", 0, 10);
                if (node->player.immunity > 0) anyImmunity = true;
            }
        }
    }

    // The recursive check models the classic rules only.
    bool canVerify = (window == 1 && !anyImmunity);
    int predicted = canVerify ? predictSurvivor(n, start, pattern, m) : 0;

    cout << "\nRing: ";
    ring.print();
    if (canVerify)
        cout << "Recursive check predicts survivor id " << predicted << "\n";

    EliminationEngine engine(ring, skips, start, window);

    if (engine.finished()) printSurvivor(ring, canVerify, predicted);

    while (true) {
        cout << "\n1 Step  2 Run to end  3 Show ring  4 Undo  5 Redo  0 Quit\n";
        int choice = readInt("Choice: ", 0, 5);
        if (choice == 0) return 0;

        if (choice == 1 || choice == 2) {
            if (engine.finished()) {
                cout << "Game is finished. Undo to go back, or quit.\n";
                continue;
            }
            if (choice == 1) engine.step();
            else engine.run();
            if (engine.finished()) printSurvivor(ring, canVerify, predicted);
        } else if (choice == 3) {
            ring.print();
        } else if (choice == 4) {
            if (!engine.undo()) cout << "Nothing to undo.\n";
        } else {
            if (!engine.canRedo()) {
                cout << "Nothing to redo.\n";
            } else {
                engine.redo();
                if (engine.finished()) printSurvivor(ring, canVerify, predicted);
            }
        }
    }
}
