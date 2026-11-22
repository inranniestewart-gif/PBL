
#include "CircularList.h"

CircularList::CircularList() : last(nullptr), count(0) {}

CircularList::~CircularList() {
    if (!last) return;
    Node* cur = last->next;
    last->next = nullptr;         
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
}

void CircularList::add(const Player& p) {
    Node* n = new Node(p);
    if (!last) {
        n->next = n;
        last = n;
    } else {
        n->next = last->next;
        last->next = n;
        last = n;
    }
    count++;
}

void CircularList::removeAfter(Node* prev) {
    Node* target = prev->next;
    prev->next = target->next;
    if (target == last) last = prev;
    delete target;
    count--;
}

void CircularList::insertAfter(Node* prev, const Player& p, bool becomesTail) {
    Node* n = new Node(p);
    n->next = prev->next;
    prev->next = n;
    if (becomesTail) last = n;
    count++;
}

Node* CircularList::findById(int id) {
    if (!last) return nullptr;
    Node* cur = last->next;
    do {
        if (cur->player.id == id) return cur;
        cur = cur->next;
    } while (cur != last->next);
    return nullptr;
}

Node* CircularList::head() { return last->next; }
Node* CircularList::tail() { return last; }
int CircularList::size() { return count; }

void CircularList::print() {
    Node* cur = head();
    do {
        cout << cur->player << "  ";
        cur = cur->next;
    } while (cur != head());
    cout << "\n";
}
