
#include <iostream>
#include <string>
#include "Player.h"
#include "CircularList.h"
#include "SkipQueue.h"
#include "EliminationEngine.h"
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

int main() {
    int n = readInt("Number of participants (2-1000): ", 2, 1000);
    int start = readInt("Starting position (1-n): ", 1, n);
    int m = readInt("How many skip values in the pattern: ", 1, 20);

    SkipQueue skips;
    for (int i = 1; i <= m; i++)
        skips.add(readInt("Skip value " + to_string(i) + ": ", 1, 1000));

    CircularList ring;
    for (int i = 1; i <= n; i++)
        ring.add(Player(i, "Player" + to_string(i)));

    cout << "\nRing: ";
    ring.print();

    EliminationEngine engine(ring, skips, start);

    while (!engine.finished()) {
        cout << "\n1 Step  2 Run to end  3 Show ring  0 Quit\n";
        int choice = readInt("Choice: ", 0, 3);
        if (choice == 0) return 0;
        if (choice == 1) engine.step();
        else if (choice == 2) engine.run();
        else ring.print();
    }

    cout << "\nFinal survivor: " << ring.head()->player << "\n";
    return 0;
}
