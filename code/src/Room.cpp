#include "Room.h"
#include <iostream>
#include <algorithm>

// Room constructor
Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description), visited(false), monster(NULL) {
}


// Room destructor
Room::~Room() {
    // Clean up monster and items

	//if monster exists, delete it
	if(monster != NULL) {
		delete monster;
	}

	//loop through items
        for(int i = 0; i < (int)items.size(); i++){
                //free each item
                delete items[i];
        }
        //actually clear the vector
        items.clear();

}


// display
// - Print formatted room information with decorative borders
// - Format:
//   ========================================
//   Room Name
//   ========================================
//   Description text
//   
//   [If monster] A MonsterName blocks your path!
//   
//   [If items] Items here:
//     - item1
//     - item2
//   
//   Exits: north, south, east
//   ========================================
//
void Room::display() const {
    // Display room information

	std::cout << "========================================" << std::endl;

	//Room Name
	std::cout << getName() << std::endl;
	std::cout << "========================================" << std::endl;

	//Description text
	std::cout << getDescription() << std::endl;
	std::cout << std::endl;

	//if monster exists and is alive
	if(hasMonster()){
		//print monster message
		std::cout << "A " << monster->getName() << " blocks your path!" << std::endl;
		std::cout << std::endl;
	}
	//if items not empty
	if(items.size() > 0){
		//loop through items vector and print the name of each item
		std::cout << "Items here:" << std::endl;
		for(int i = 0; i < (int)items.size(); i++){
			std::cout << " - " << items[i]->getName() << std::endl;
		}
		std::cout << std::endl;
	}

	//Display the exits
	//flag to prevent comma from being printed before first exit
	bool comma = false;

	//loop through map and print comma (if flag), then name of exit
	std::cout << "Exits: ";
	for(std::map<std::string, Room*>::const_iterator it = exits.begin(); it != exits.end(); ++it){
		if(comma){
			std::cout << ", ";
		}
		comma = true;
		std::cout << it->first;
	}

	std::cout << std::endl;
	std::cout << "========================================" << std::endl;
}


// displayExits
// - Print "Exits: "
// - Iterate through exits map using iterator
// - Print each direction (the key) separated by commas
// - Example output: "Exits: north, south, east"
//
void Room::displayExits() const {
    // Display available exits

	//this is exactly the same as the printing exits part of the previous method
	bool comma = false;
        std::cout << "Exits: ";
        for(std::map<std::string, Room*>::const_iterator it = exits.begin(); it != exits.end(); ++it){
                if(comma){
                        std::cout << ", ";
                }
                comma = true;
                std::cout << it->first;
        }

        std::cout << std::endl;
}


// addExit
// - Check if room pointer is not NULL
// - Add to exits map: exits[direction] = room
//
void Room::addExit(const std::string& direction, Room* room) {
    // Add exit to map
	//if room is null, leave
	if(room == NULL) { return; }

	//add room to exits map with direction as key
	exits[direction] = room;

}


// getExit
// - Look up direction in exits map
// - Use exits.find(direction)
// - If not found, return NULL
//
Room* Room::getExit(const std::string& direction) const {
    // Look up and return exit

	//look up direction in exits map
	std::map<std::string, Room*>::const_iterator it = exits.find(direction);

	//create place for room pointer
	Room* lookUp = NULL;

	//if key exists
	if(it != exits.end()){
		//assign room ptr to lookup
		lookUp = it->second;
	}

	//if found, return ptr to the room
	if(lookUp){ return lookUp; }

	//otherwise return null
	return NULL;
}


// hasExit
// - Check if direction exists in exits map
bool Room::hasExit(const std::string& direction) const {
    // Check if exit exists

        //look up direction in exits map
        std::map<std::string, Room*>::const_iterator it = exits.find(direction);

	//if it exists
	if(it != exits.end()){
		//return true
		return true;
	}

	//otherwise
	return false;
}


// clearMonster
// - If monster exists, delete it
// - Set monster pointer to NULL
//
void Room::clearMonster() {
    // Delete and clear monster
	if(monster){
		delete monster;
	}
	monster = NULL;
}


// addItem
// - Check if item pointer is not NULL
// - Add to items vector using push_back()
//
void Room::addItem(Item* item) {
    // Add item to room

	//if item ptr is NULL, leave
	if(item == NULL) { return; }

	//add item to vector
	items.push_back(item);
}


// removeItem
// - Search items vector for item by name (case-insensitive)
// - If found: erase from vector (DON'T delete - ownership transferred)
//
void Room::removeItem(const std::string& item_name) {
    // Find and remove item from room

	//assign name to s1
	std::string s1 = item_name;

        //make s1 lowercase
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

        //place holder for string in inventory
        std::string s2;

        //flag to see if found
        bool found = false;

        //foe each item in inventory
        for(int i = 0; i < (int)items.size(); i++) {
                //put item name into s2
                s2 = items[i]->getName();

                //make s2 lowercase
                std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                //if names are identical
                if(s1 == s2){
                        //remove item from inventory (without deleting)
                        items.erase(items.begin() + i);
                        //set found flag
                        found = true;
                        //break
                        break;
                }

        }
        //if not found
        if(!found){
                //print error message
                std::cout << "Error: Item not found!" << std::endl;
        }
}


// displayItems
// - Print each item's name in a list
// - Format: "  - ItemName"
//
void Room::displayItems() const {
    // Display all items in room
        for(int i = 0; i < (int)items.size(); i++){
                std::cout << " - " << items[i]->getName() << std::endl;
        }
}


// getItem
// - Search items vector for item by name (case-insensitive)
// - If found, return pointer to item
// - If not found, return NULL
//
Item* Room::getItem(const std::string& item_name) {
    // Find and return item pointer

        //copy parameter to modify in s1
        std::string s1 = item_name;

        //make s1 lowercase
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

        //place holder for string in inventory
        std::string s2;

        for(int i = 0; i < (int)items.size(); i++){
                //put item name into s2
                s2 = items[i]->getName();

                //make s2 lowercase
                std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                //if names are identical
                if(s1 == s2){
                        //return pointer to item
                        return items[i];
                }
        }

        //if not found, return NULL
        return NULL;
}
