#include <vector>
#include "Item.h"

/*

**Goal**: Create a simple test program that manages a vector of items

1. Create a test program (`test_inventory.cpp`)
2. Create a `std::vector<Item*>` to hold items
3. Add several items (weapons, armor, consumables)
4. Display all items
5. Remove an item by name (search and erase)
6. **IMPORTANT**: Delete all items before program ends

*/

int main() {
    std::vector<Item*> inventory;

    // Add items
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Heals", 20));

    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }

    // Clean up - VERY IMPORTANT!
    for (int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();

    return 0;
}
