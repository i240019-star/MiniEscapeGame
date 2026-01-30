#include "Room.h"
#include <iostream>
using namespace std;
void showMenu();
int readInt();
int main() 
{
    Room room;
    // First we are populating room with initial items (IDs are choosen chosen arbitrarily)
    // 1: Old Gear Key (collectable), 2: Brass Oil Can, 3: Note Part 1, 4: Note Part 2
    // 5: Locked Box (not collectable), 6: Working Key (result), 7: Complete Note (result)
    room.addItem(new Item(1,"Rust-Covered Gear Key", "A metallic key shaped like a gear, jammed with rust.\nHINT:(It can be combine with Oil to make a functional key.)", true));
    room.addItem(new Item(2,"Brass Oil Can", "A small  can  filled with oil.Ooh! It smells like old machinery.\nHINT:(It can be used to clean the Rust-Covered Gear Key.)", true));
    room.addItem(new Item(3,"Note Part 1", "Part 1 of a torn note.\nHINT:(It contains part of a code.)", true));
    room.addItem(new Item(4,"Note Part 2", "Part 2 of a torn note.\nHINT:(It  contains the rest of a code.)", true));
    room.addItem(new Item(5,"Locked Box", "A small locked box.\nHINT:(Maybe a code will open it.)", false));

    // inventory (max 10)
    Item* inventory[10]={nullptr};
    int invCount=0;

    bool solvedBox=false;
    bool completeNote=false;
    bool hasWorkingKey=false;
    bool gameRunning=true;

    while (gameRunning) 
    {
        showMenu();
        int choice=readInt();
        switch (choice) {
            case 1: 
            { // Look around the room 
                room.lookAround();
                break;
            }
            case 2: 
            { // Examine item by ID 
                cout<<"Enter item ID to examine: ";
                int id=readInt();
                Item* it=room.findItemById(id); //search item in room
                if (!it) 
                {
                    // search item in the  inventory if not find in room
                    for (int i=0;i<invCount;i++) 
                    {
                        if (inventory[i] && inventory[i]->getId()==id) 
                        { 
                            it=inventory[i]; 
                            break; 
                        }
                    }
                }
                if (!it) //if item is still not in inventory then item is not found
                {
                    cout<<"Item not found.Try again.\n";
                } else 
                {
                    it->display(true); // if item is found show its details
                }
                break;
            }
            case 3: 
            { // Pick up items max 10
                cout<<"Enter item ID to pick up: ";
                int id=readInt();
                if (invCount>=10) 
                {
                     cout<<"Inventory is full! Drop something before picking up.\n"; 
                     break; 
                }
                Item* it=room.findItemById(id); //Search room for item
                if (!it)  //if not found in the room, stop and show error
                { 
                    cout<<"OOP! No such item in the room.\n"; 
                    break; 
                }
                if (!it->isCollectable()) //Check if the item can be picked up
                {
                    cout<<"This item cannot be picked up.\n"; 
                     break; 
                }
                // clone item into inventory (room keeps original for reference)
                Item* copy=it->clone();
                inventory[invCount++] = copy;
                cout<<"Picked up: "<< copy->getName()<<"\n";
                break;
            }
            case 4: 
            { // View inventory
                cout<<"Inventory (" << invCount << "/10):\n";
                for (int i = 0; i<invCount;i++) 
                {
                    if (inventory[i]) 
                    inventory[i]->display();
                }
                break;
            }
            case 5: 
            { // Use item
                cout<<"Enter item ID from inventory to use it: ";
                int id=readInt();
                int idx=-1;
                for (int i = 0;i<invCount;i++) if (inventory[i] && inventory[i]->getId() == id) { idx = i; break; }
                if (idx==-1) {cout<<"You don't have this item.\n"; break; }
                Item* it=inventory[idx];
                // Using notes to find code or using key on box
                if (it->getId()==3 || it->getId() == 4) 
                {
                    cout<<"Examining the note: "<<it->getDescription()<<"\n";
                }
                else if (it->getId()==7) 
                {
                    if (!solvedBox) 
                    {
                        solvedBox = true;
                        cout<<"You used the complete note code to open the locked box ! Inside is a small gadget needed to escape.\n";
                    } 
                    else 
                    {
                        cout<<"You have already opened the box.\n";
                    }
                     }
            
                else if (it->getId() == 6) 
                {
                    // working key can open box
                    if (!solvedBox) 
                    {
                        solvedBox = true;
                        cout<<"You used the working key to open the locked box! Inside is a small gadget needed to escape.\n";
                    } else 
                    {
                        cout<<"You have already opened the box.\n";
                    }
                }
                else 
                {
                    cout<<"Using "<<it->getName()<<" has no immediate effect.\n";
                }
                break;
            }
            case 6: 
            { // Combine two items
                cout<<"Enter first item ID from inventory: ";
                int first=readInt();
                cout<<"Enter second item ID from inventory: ";
                int second=readInt();
                int ia = -1, ib = -1;
                for (int i = 0; i < invCount; ++i) {
                    if (inventory[i] && inventory[i]->getId() == first) ia = i;
                    if (inventory[i] && inventory[i]->getId() == second) ib = i;
                }
                if (ia == -1 || ib == -1) {cout << "One or both items not in inventory.\n"; break; }
                // combination rules
                if ((first == 1 && second == 2) || (first == 2 && second == 1)) {
                    //  Key + Oil -> Working Key (id 6)
                    Item *working=new Item(6, "Working Key", "A now-working key after oiling.", true);
                    // remove both originals from inventory (delete)
                    delete inventory[ib]; inventory[ib] = inventory[invCount-1]; inventory[invCount-1] = nullptr; --invCount;
                    // ensure indices adjusted if ia was last
                    if (ia >= invCount) ia = -1; // reused slot
                    if (ia != -1) { delete inventory[ia]; inventory[ia] = inventory[invCount-1]; inventory[invCount-1] = nullptr; --invCount; }
                    // add new
                    if (invCount < 10) inventory[invCount++] = working;
                    cout << "Combined and created: " << working->getName() << "\n";
                    hasWorkingKey = true;
                } else if ((first == 3 && second == 4) || (first == 4 && second == 3)) {
                    // Note parts combine to complete note (id 7)
                    Item *note = new Item(7, "Complete Note", "This note reveals the code: 1-4-2", true);
                    // remove two parts similar to above
                    delete inventory[ib]; inventory[ib] = inventory[invCount-1]; inventory[invCount-1] = nullptr; --invCount;
                    if (ia >= invCount) ia = -1;
                    if (ia != -1) { delete inventory[ia]; inventory[ia] = inventory[invCount-1]; inventory[invCount-1] = nullptr; --invCount; }
                    if (invCount < 10) inventory[invCount++]=note;
                    cout << "Combined notes into: " << note->getName() << "\n";
                    completeNote = true;
                } else {
                    cout << "Those items cannot be combined.\n";
                }
                break;
            }
            case 7: { // Check progress
                cout << "Progress:\n";
                cout << " - Working key: " << (hasWorkingKey ? "YES" : "NO") << "\n";
                cout << " - Complete Note: " << (completeNote ? "YES" : "NO") << "\n";
                cout << " - Box opened: " << (solvedBox ? "YES" : "NO") << "\n";
                break;
            }
            case 8: { // Try to escape
                if ((solvedBox && hasWorkingKey)||(solvedBox && completeNote)) 
                {
                    cout << " CONGRATULATIONS!You used the required items and escapeds!\n";
                    gameRunning = false;
                } 
                else 
                {
                    cout<<"OOPS!You are not ready to escape.Solve more puzzles.\n";
                }
                break;
            }
            case 9: {
                cout << "Exiting game. Goodbye.\n";
                gameRunning = false;
                break;
            }
            default:
                cout << "Invalid choice, try again.\n";
        } // end switch
    } // end while

    // cleanup inventory (delete items)
    for (int i = 0; i < invCount; ++i) delete inventory[i];

    return 0;
}

// helper functions
void showMenu() 
{
         cout << "====== ESCAPE ROOM ======\n"
              << "1. Look around room\n"
              << "2. Examine item (by ID)\n"
              << "3. Pick up item\n"
              << "4. View inventory\n"
              << "5. Use item\n"
              << "6. Combine two items\n"
              << "7. Check progress\n"
              << "8. Try to escape\n"
              << "9. Exit game\n"
              << "=========================\n"
              << "Enter choice: ";
}

int readInt() 
{
    int x;
    while (!(cin >> x)) 
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid number. Enter again: ";
    }
    return x;
}
