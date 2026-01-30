#include "Item.h"
using namespace std;
// initialize static
int Item::createdCount = 0;

char* Item::duplicateStr(const char *s) 
{
    if (!s) return nullptr;
    int len=0;
    while (s[len] !='\0')
    {
    len++;
    }
    char *p = new char[len + 1];
    for (int i = 0; i <= len;i++) p[i] = s[i];
    return p;
}

// full constructor 
Item::Item(int iid, const char *iname, const char *desc, bool canCollect)
: id(iid), name(nullptr), description(nullptr), collectable(canCollect), resultId(0), used(false)
{
    name = duplicateStr(iname);
    description = duplicateStr(desc);
    ++createdCount;
}

// overloaded constructor (only name given)
Item::Item(int iid, const char *iname)
: id(iid), name(nullptr), description(nullptr), collectable(false), resultId(0), used(false)
{
    name = duplicateStr(iname);
    description = duplicateStr("");
    ++createdCount;
}

// deep copy constructor
Item::Item(const Item &other)
: id(other.id), name(nullptr), description(nullptr), collectable(other.collectable),
  resultId(other.resultId), used(other.used)
{
    name = duplicateStr(other.name);
    description = duplicateStr(other.description);
    ++createdCount;
}

Item::~Item() {
    delete [] name;
    delete [] description;
    // we intentionally do NOT decrement createdCount here — createdCount is total created over runtime.
    // If you prefer active count, decrement here.
}

// chaining: mark as collectable
Item& Item::makeCollectable() {
    this->collectable = true;
    return *this; // this pointer usage and chaining
}

// chaining: set combination result id
Item& Item::setResult(int rid) {
    this->resultId = rid;
    return *this;
}

// basic display (const correctness)
void Item::display() const {
    cout << "ID " << id << " | " << (name ? name : "(no name)");
    if (collectable) cout << " [collectable]";
    if (used) cout << " [used]";
    cout << "\n  Desc: " << (description ? description : "") << "\n";
}

// overloaded display with verbose flag (function overloading #1)
void Item::display(bool verbose) const {
    display();
    if (verbose) {
        cout << "  (Result if combined: " << resultId << ")\n";
    }
}

Item* Item::clone() const {
    return new Item(*this); // uses copy ctor
}

// getters
int Item::getId() const { return id; }
const char* Item::getName() const { return name; }
const char* Item::getDescription() const { return description; }
bool Item::isCollectable() const { return collectable; }
int Item::getResultId() const { return resultId; }
bool Item::isUsed() const { return used; }

void Item::markUsed() { used = true; }

// replace description (demonstrates function overloading #2 if we added another setDescription signature)
// but here we implement single method.
void Item::setDescription(const char *desc) {
    delete [] description;
    description = duplicateStr(desc);
}

int Item::totalCreated() { return createdCount; }
