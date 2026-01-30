#ifndef ITEM_H
#define ITEM_H

#include <iostream>
class Item
{
private:
    const int id;          // unique id 
    char *name;            // dynamically allocated string
    char *description;     // dynamically allocated string
    bool collectable;
    int resultId;          // if used in combination, resulting item id (0=none)
    bool used;             // whether item has been used/consumed
    static int createdCount;

    // helper for copying C-strings
    static char* duplicateStr(const char *s);
    public:
    // constructors
    Item(int id, const char *name, const char *desc, bool collectable);
    Item(int id, const char *name);                    // overloaded constructor
    Item(const Item &other);                           // deep-copy constructor

    // destructor
    ~Item();

    // method chaining: return *this (use this pointer)
    Item& makeCollectable();                           // mark collectable
    Item& setResult(int rid);                          // set result id when combined

    // actions
    void display() const;                              // basic display
    void display(bool verbose) const;                  // overloaded display (function overloading #1)
    Item* clone() const;                               // deep copy helper

    // getters
    int getId() const;
    const char* getName() const;
    const char* getDescription() const;
    bool isCollectable() const;
    int getResultId() const;
    bool isUsed() const;

    // utility
    void markUsed();                                   // mark as used
    void setDescription(const char *desc);             // replace description
    static int totalCreated();                         // static member access
};

#endif
