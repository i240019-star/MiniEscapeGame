#ifndef ROOM_H
#define ROOM_H

#include "Item.h"

class Room {
private:
    Item* items[10];    // up to 10 items in the room
    int count;
    static int roomCount;

public:
    Room();
    ~Room();

    bool addItem(Item* it);               // add item pointer (ownership)
    bool addItem(int id, const char *name, const char *desc); // overloaded (function overloading #2)
    Item* removeItemById(int id);         // remove and return pointer (caller owns returned item)
    Item* findItemById(int id) const;     // non-destructive search (returns pointer or nullptr)

    void lookAround() const;              // display items in the room
    static void displayPuzzleItems(const Item* items, int count, int puzzleID); // required function signature

    int getCount() const;
};

#endif
