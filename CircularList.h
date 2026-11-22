
#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "Player.h"

struct Node {
    Player player;
    Node* next;
    Node(const Player& p) : player(p), next(nullptr) {}
};

class CircularList {
    Node* last;   
    int count;

public:
    CircularList();
    ~CircularList();

    void add(const Player& p);      
    void removeAfter(Node* prev);    
    void insertAfter(Node* prev, const Player& p, bool becomesTail);
    Node* findById(int id);
    Node* head();
    Node* tail();
    int size();
    void print();
};

#endif
