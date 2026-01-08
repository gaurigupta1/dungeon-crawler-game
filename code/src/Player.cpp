#include "Player.h"
#include <iostream>
#include <algorithm>

// Player constructor
// - MUST call Character base constructor. 
//
Player::Player(const std::string& name)
    : Character(name, 100, 10, 5),
      level(1), experience(0), gold(0),
      equipped_weapon(NULL), equipped_armor(NULL) {
}


// Player destructor
// - CRITICAL: Must delete all items in inventory to prevent memory leaks!
// - DON'T delete equipped_weapon or equipped_armor - they point to items
//   already in the inventory, so they're already deleted!
//
Player::~Player() {
    // Delete all inventory items

	//loop through inventory
	for(int i = 0; i < (int)inventory.size(); i++){
		//free each item in inventory
		delete inventory[i];
	}
	//actually clear the vector
	inventory.clear();
}


// Override displayStats
// - Show player-specific information
// - Include: level, HP, attack (with weapon bonus), defense (with armor bonus), gold, experience
// - Show equipped weapon and armor names if any
// - Use decorative formatting (borders, headers)
// - Use getters to access inherited Character data
//
void Player::displayStats() const {
    // Display comprehensive player stats

	//set weaponBonus and armorBonus so its not just null
	int weaponBonus = (equipped_weapon) ? equipped_weapon->getValue() : 0;
	int armorBonus = (equipped_armor) ? equipped_armor->getValue() : 0;

	//print divider
	std::cout << "--------------------" << std::endl;

	//print name
	std::cout << "[PLAYER] " << getName() << std::endl;

	//print level
	std::cout << "  Level: " << getLevel() << std::endl;

	//print current HP
	std::cout << "  HP: " << getCurrentHP() << std::endl;

	//print attack and weapon bonus
	std::cout << "  Attack: " << getAttack() << " (Weapon Bonus: " << weaponBonus << ")" << std::endl;

	//print defense and armor bonus
	std::cout << "  Defense: " << getDefense() << " (Armor Bonus: " << armorBonus << ")" << std::endl;

	//print gold
	std::cout << "  Gold: " << getGold() << std::endl;

	//print experience
	std::cout << "  Experience: " << getExperience() << std::endl;

	//print divider
	std::cout << "--------------------" << std::endl;
}


// Override calculateDamage to include weapon bonus
// - If weapon is equipped, add weapon's damage bonus
// - Return total damage
//
int Player::calculateDamage() const {
    // Calculate damage with weapon bonus
	//get initial attack damage
	int newDamage = getAttack();

	//if weapon is equipped
	if(equipped_weapon){
		//add weapon damage and attack damage to get total damage
		newDamage += equipped_weapon->getValue();
	}

	//return total damage
	return newDamage;
}


// addItem
// - Add item to inventory vector using push_back()
// - Print pickup message with item name
//
void Player::addItem(Item* item) {
    // Add item to inventory

	//check if item is NULL
	if(item == NULL){

	//don't add a NULL item
		return;
	}

	//add item to inventory
	inventory.push_back(item);

	//Tell user that they "picked up" the item (added it to their inventory)
	std::cout << "You picked up: " << item->getName() << std::endl;
}


//  removeItem
// - Search inventory for item by name (case-insensitive comparison)
// - If found: delete the item, then erase from vector
// - If not found: print error message
// - Remember: inventory.erase(inventory.begin() + i) to remove at index i
//
void Player::removeItem(const std::string& item_name) {
    // Find and remove item from inventory

	//copy parameter to modify in s1
	std::string s1 = item_name;

	//make s1 lowercase
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

	//place holder for string in inventory
	std::string s2;

	//flag to see if found
	bool found = false;

	//foe each item in inventory
	for(int i = 0; i < (int)inventory.size(); i++) {
		//put item name into s2
		s2 = inventory[i]->getName();

		//make s2 lowercase
		std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		//if names are identical
		if(s1 == s2){
			//delete item
			delete inventory[i];
			//remove item from inventory
			inventory.erase(inventory.begin() + i);
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


// displayInventory
// - Print header: "----- Inventory -----"
// - If inventory is empty, print "Empty"
// - Otherwise, loop through and print each item's name and type
// - Format: "- ItemName (ItemType)"
// - Print footer: "--------------------"
//
void Player::displayInventory() const {
    // Display all items in inventory

	//print header
	std::cout << "----- Inventory -----" << std::endl;

	//if empty, skip to printing footer
	if(inventory.size() == 0){
		std::cout << "Empty" << std::endl;
		goto print_end;
	}

	//print each item in inventory (name and type)
	for(int i = 0; i < (int)inventory.size(); i++){
		std::cout << "- " << inventory[i]->getName() << " (" << inventory[i]->getType() << ")" << std::endl;
	}
	//print footer
	print_end:
		std::cout << "--------------------" << std::endl;
}


// hasItem
// - Search inventory for item by name (case-insensitive)
// - Return true if found, false otherwise
// - Use same case-insensitive comparison as removeItem
//
bool Player::hasItem(const std::string& item_name) const {
    // Check if item exists in inventory

	//copy parameter to modify in s1
        std::string s1 = item_name;

        //make s1 lowercase
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

        //place holder for string in inventory
        std::string s2;

        //print each item in inventory (name and type)
        for(int i = 0; i < (int)inventory.size(); i++){
                //put item name into s2
                s2 = inventory[i]->getName();

                //make s2 lowercase
                std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                //if names are identical
                if(s1 == s2){
			//return true
                        return true;
                }
	}

	//if not found, return false
	return false;
}


// getItem
// - Search inventory for item by name (case-insensitive)
// - Return pointer to item if found
// - Return NULL if not found
//
Item* Player::getItem(const std::string& item_name) {
    // Find and return item pointer

        //copy parameter to modify in s1
        std::string s1 = item_name;

        //make s1 lowercase
        std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);

        //place holder for string in inventory
        std::string s2;

        for(int i = 0; i < (int)inventory.size(); i++){
                //put item name into s2
                s2 = inventory[i]->getName();

                //make s2 lowercase
                std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

                //if names are identical
                if(s1 == s2){
			//return pointer to item
                        return inventory[i];
                }
        }

        //if not found, return NULL
        return NULL;
}


// equipWeapon
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Weapon"
// - If current weapon equipped, print unequip message
// - Set equipped_weapon pointer to this item
// - Print equip message
//
void Player::equipWeapon(const std::string& weapon_name) {
    // Equip weapon from inventory

	//get pointer to weapon from inventory
	Item* equip = getItem(weapon_name);

	//if NULL (not there)
	if(equip == NULL) {
		//print error message
		std::cout << "Error: " << weapon_name << " not found." << std::endl;
		//return
		return;
	}

	//get item type to make sure it is a weapon
	std::string itemType = equip->getType();

	//make it lowercase for comparison
	std::transform(itemType.begin(), itemType.end(), itemType.begin(), ::tolower);

	//if correct type (weapon)
	if(itemType == "weapon"){
		//if already equipped, print already equipped message
		if(equipped_weapon == equip) {
			std::cout << weapon_name << " already equipped." << std::endl;
		}
		//otherwise, equip, and print equip message
		else {
			equipped_weapon = equip;
			std::cout << weapon_name << " equipped." << std::endl;
		}
	}
}


// equipArmor
// - Similar to equipWeapon but for armor
// - Check if item type is "Armor"
// - Set equipped_armor pointer
//
void Player::equipArmor(const std::string& armor_name) {
    // Equip armor from inventory

        //get pointer to armor from inventory
        Item* equip = getItem(armor_name);

        //if NULL (not there)
        if(equip == NULL) {
                //print error message
                std::cout << "Error: " << armor_name << " not found." << std::endl;
                //return
                return;
        }

        //get item type to make sure it is armor
        std::string itemType = equip->getType();

        //make it lowercase for comparison
        std::transform(itemType.begin(), itemType.end(), itemType.begin(), ::tolower);

        //if correct type (armor)
        if(itemType == "armor"){
                //if already equipped, print already equipped message
                if(equipped_armor == equip) {
                        std::cout << armor_name << " already equipped." << std::endl;
                }
                //otherwise, equip, and print equip message
                else {
                        equipped_armor = equip;
                        std::cout << armor_name << " equipped." << std::endl;
                }
        }
}


// unequipWeapon
// - Check if weapon is currently equipped
// - If so, print message and set equipped_weapon to NULL
// - If not, print error message
//
void Player::unequipWeapon() {
    // Unequip current weapon

	//if weapon not equipped
	if(!equipped_weapon) {
		//print error message
		std::cout << "Error: No weapon equipped." << std::endl;
		//return
		return;
	}

	//if weapon is equipped
	else{
		//print unequipped message
		std::cout << "[WEAPON]: " << equipped_weapon << " unequipped." << std::endl;

		//set equipped_weapon to NULL
		equipped_weapon = NULL;
	}
}


// unequipArmor
// - Similar to unequipWeapon
// - Set equipped_armor to NULL
//
void Player::unequipArmor() {
    // Unequip current armor

        //if armor not equipped
        if(!equipped_armor) {
                //print error message
                std::cout << "Error: No armor equipped." << std::endl;
                //return
                return;
        }

        //if armor is equipped
        else{
                //print unequipped message
                std::cout << "[ARMOR]: " << equipped_armor << " unequipped." << std::endl;

                //set equipped_armor to NULL
                equipped_armor = NULL;
        }
}


// useItem
// - Get item from inventory using getItem()
// - Check if item exists (not NULL)
// - Check if item type is "Consumable"
// - Cast to Consumable*: Consumable* consumable = static_cast<Consumable*>(item)
// - Check if already used: consumable->isUsed()
// - Get healing amount: consumable->getHealingAmount()
// - Call heal() with that amount
// - Call consumable->use() to mark as used
// - Remove item from inventory (it's been consumed!)
//
void Player::useItem(const std::string& item_name) {
    // Use consumable item

	//get pointer to item from inventory
        Item* item = getItem(item_name);

        //if NULL (not there)
        if(item == NULL) {
                //print error message
                std::cout << "Error: " << item_name << " not found." << std::endl;
                //return
                return;
        }

	//if there
	else{
		//if item type is "Consumable"
		if(item->getType() == "Consumable"){

			//Cast to Consumable*
			Consumable* consumable = static_cast<Consumable*>(item);

			//Check if already used
			if(!consumable->isUsed()){

				//Call heal() with healing amount
				heal(consumable->getHealingAmount());

				//Call consumable->use() to mark as used
				consumable->use();

				//remove item from inventory
				removeItem(item_name);
			}

			//if already used
			else{
				std::cout << "Error: " << item_name << " already used." << std::endl;
			}
		}

		//if item is not consumable
		else {
			//print error statement, not consumable
			std::cout << "Error: " << item_name << " is not consumable." << std::endl;
		}
	}
}


// gainExperience
// - Add experience points
// - Print message showing exp gained
// - Check if enough exp to level up: if (experience >= level * 100)
// - If so, call levelUp()
//
void Player::gainExperience(int exp) {
    // Add experience and check for level up

	//Add experience points
	experience += exp;

	//print message showing exp gained
	std::cout << "+" << exp << " XP!" << std::endl;

	//check if enough exp to level up
	if(experience >= level * 100)
		levelUp();
}


// levelUp
// - Increment level
// - Reset experience to 0
// - Increase stats:
//   * Increase max_hp by 10 (use setMaxHP())
//   * Set current_hp to max (full heal on level up)
//   * Increase attack by 2
//   * Increase defense by 1
// - Print celebratory level up message
// - Display new stats
//
void Player::levelUp() {
    // Level up the player

	//increment level
	level++;

	//reset experience to 0
	experience = 0;

	//increase max_hp by 10
	setMaxHP(getMaxHP() + 10);

	//set current_hp to max
	setCurrentHP(getMaxHP());

	//increase attack by 2
	setAttack(getAttack() + 2);

	//increase defense by 1
	setDefense(getDefense() + 1);

	//Print celebratory level up message
	std::cout << "Yay! " << getName() << " leveled up!" << std::endl;

	//display stats
	displayStats();

}
