#include "Room.h"
#include <iostream>
using namespace std;
int Room::roomCount = 0;

Room::Room() : count(0) {
    for (int i = 0; i < 10; ++i) items[i] = nullptr;
    ++roomCount;
}

Room::~Room() {
    // free any items we still own
    for (int i = 0; i < 10; ++i) {
        delete items[i];
        items[i] = nullptr;
    }
    --roomCount;
}

// add item pointer (if there's space)
bool Room::addItem(Item* it) {
    if (!it) return false;
    if (count >= 10) return false;
    for (int i = 0; i < 10; ++i) {
        if (items[i] == nullptr) {
            items[i] = it;
            ++count;
            return true;
        }
    }
    return false;
}

// overloaded addItem to demonstrate function overloading (creates a new Item and adds it)
bool Room::addItem(int id, const char *name, const char *desc) {
    Item *it = new Item(id, name, desc, true);
    return addItem(it);
}

// remove and return item pointer by id (caller takes ownership)
Item* Room::removeItemById(int id) {
    for (int i = 0; i < 10; ++i) {
        if (items[i] != nullptr && items[i]->getId() == id) {
            Item* it = items[i];
            items[i] = nullptr;
            --count;
            return it;
        }
    }
    return nullptr;
}

Item* Room::findItemById(int id) const {
    for (int i = 0; i < 10; ++i) {
        if (items[i] != nullptr && items[i]->getId() == id) return items[i];
    }
    return nullptr;
}

void Room::lookAround() const {
    cout << "You look around the room. Items visible:\n";
    for (int i = 0; i < 10; ++i) {
        if (items[i]) {
            cout << " - ";
            items[i]->display();
        }
    }
}

// displays items relevant to a puzzle id (simple demonstration)
void Room::displayPuzzleItems(const Item* its, int cnt, int puzzleID) {
    cout << "Puzzle " << puzzleID << " related items:\n";
    for (int i = 0; i < cnt; ++i) {
        if (its[i].getId() != 0) {
            its[i].display();
        }
    }
}

int Room::getCount() const { return count; }
