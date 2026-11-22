#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player {
public:
    int id;
    string name;
    int weight;     
    int immunity;   

    Player(int id = 0, string name = "") : id(id), name(name), weight(1), immunity(0) {}
    ~Player() {}

    bool operator==(const Player& other) const { return id == other.id; }

    friend ostream& operator<<(ostream& os, const Player& p) {
        return os << p.name << " (id " << p.id << ")";
    }
};

#endif
