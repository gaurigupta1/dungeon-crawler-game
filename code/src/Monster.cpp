#include "Monster.h"
#include <iostream>

// ============================================================================
// Base Monster class
// ============================================================================

// Monster constructor
// - MUST call Character base constructor
// - Initialize experience_reward and gold_reward
// - Loot table starts empty automatically
//
Monster::Monster(const std::string& name, int hp, int attack, int defense,
                 int exp_reward, int gold_reward)
    : Character(name, hp, attack, defense),
      experience_reward(exp_reward), gold_reward(gold_reward) {
}


// Monster destructor
// - Deallocate any allocated memory 
// - Loop through loot_table vector and delete each Item*
// - Clear the vector after deleting items
//
Monster::~Monster() {
        //loop through loot table
        for(int i = 0; i < (int)loot_table.size(); i++){
                //free each item in loot table
                delete loot_table[i];
        }
        //actually clear the vector
        loot_table.clear();
}


// Override displayStats
// - Show monster name and HP
// - Format: "MonsterName [HP: current/max]"
// - Keep it simple - monsters don't need detailed stats display
//
void Monster::displayStats() const {
    // Display monster stats

	//Display monster name and HP
	std::cout << getName() << " [HP: " << getCurrentHP() << "/" << getMaxHP() << "]" << std::endl;
}


// addLoot
// - Check if item pointer is not NULL
// - Add item to loot_table vector using push_back()
//
void Monster::addLoot(Item* item) {
    // Add item to loot table

	//check if loot is NULL
	if(item == NULL){
		//print error message
		std::cout << "Error: loot is NULL" << std::endl;
		//return
		return;
	}

	//otherwise
	else{
		//put loot in vector
		loot_table.push_back(item);
	}

}


// dropLoot
// - Create a copy of the loot_table vector
// - Clear the original loot_table (transfer ownership to caller!)
// - Return the copy
// - This is important: caller now owns the items and must delete them
//
std::vector<Item*> Monster::dropLoot() {
    // Return loot and transfer ownership

	//create copy vector
	std::vector<Item*> lootCopy;

	//loop through original vector
	for(int i = 0; i < (int)loot_table.size(); i++){
		//put each element of loot_table in copy vector
		lootCopy.push_back(loot_table[i]);
	}

	//Clear the original loot_table
	loot_table.clear();

    return lootCopy;
}


// getAttackMessage (base version)
// - Return default attack message
// - Format: "MonsterName attacks!"
// - Use getName() to get monster's name
//
std::string Monster::getAttackMessage() const {
    // Return attack message

	//concatinate monster name and attack message
	std::string attackMessage = getName() + " attacks!";

	//return full message
	return attackMessage;
}


// ============================================================================
// Goblin - Weak but common enemy
// ============================================================================

// Goblin constructor
// - Call Monster constructor with these stats:
//   * Name: "Goblin"
//   * HP: 30
//   * Attack: 5
//   * Defense: 2
//   * Experience: 10
//   * Gold: 5
// - Add a small potion to loot table
// - Example: addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
//
Goblin::Goblin() 
    : Monster("Goblin", 30, 5, 2, 10, 5) {
    // Add loot items

	//add a small potion to loot table
	addLoot(new Consumable("Small Potion", "Restores 10 HP", 10));
}


// Override getAttackMessage for Goblin
// - Return goblin-specific attack message
// - Example: "The goblin swipes at you with its rusty dagger!"
//
std::string Goblin::getAttackMessage() const {
    // Return goblin attack message

	//assign message to string
	std::string message = "The goblin swipes at you with its rusty dagger!";

	//return string
	return message;
}


// ============================================================================
// Skeleton - Undead warrior
// ============================================================================

// Skeleton constructor
// - Call Monster constructor with these stats:
//   * Name: "Skeleton"
//   * HP: 40
//   * Attack: 8
//   * Defense: 4
//   * Experience: 20
//   * Gold: 10
// - Add an old sword to loot table
//
Skeleton::Skeleton()
    : Monster("Skeleton", 40, 8, 4, 20, 10) {
    // Add loot items

	//add old sword to loot table
	addLoot(new Weapon("Old Sword", "Causes 10 HP of damage", 10));
}


// Override getAttackMessage for Skeleton
// - Return skeleton-specific attack message
// - Example: "The skeleton rattles its bones and slashes with a sword!"
//
std::string Skeleton::getAttackMessage() const {
    // Return skeleton attack message

	//populate string with skeleton attack message
	std::string skeletonMessage = "The skeleton rattles its bones and slashes with a sword!";

	//return the string
	return skeletonMessage;
}


// ============================================================================
// Dragon - Boss enemy with special ability
// ============================================================================

// Dragon constructor
// - Call Monster constructor with these stats:
//   * Name: "Dragon"
//   * HP: 150
//   * Attack: 20
//   * Defense: 10
//   * Experience: 100
//   * Gold: 50
// - Add legendary loot:
//   * Dragon Slayer sword (damage +10)
//   * Dragon Scale Armor (defense +8)
//   * Greater Health Potion (heals 100 HP)
//
Dragon::Dragon()
    : Monster("Dragon", 150, 20, 10, 100, 50) {
    // Add legendary loot items

	//add dragon slayer sword with 10 damage
	addLoot(new Weapon("Dragon Slayer Sword", "Causes 10 HP of damage", 10));

	//add dragon scale armor with 8 defense
	addLoot(new Armor("Dragon Scale Armor", "Defense +8 HP", 8));

	//add greather health potion with 100 healing
	addLoot(new Consumable("Greater Health Potion", "Heals 100 HP", 100));
}


// Override getAttackMessage for Dragon
// - Return dragon-specific attack message
// - Example: "The dragon breathes fire at you!"
//
std::string Dragon::getAttackMessage() const {
    // Return dragon attack message
    return "The dragon breathes fire at you!";
}


// Override calculateDamage for Dragon
// - Call Monster::calculateDamage() to get base damage
// - Add bonus fire damage (+5)
// - Return total damage
// - This makes the dragon hit harder than other monsters!
//
int Dragon::calculateDamage() const {
    // Calculate damage with fire bonus

	//Call Monster::calculateDamage() to get base damage, Add bonus fire damage (+5)
	int totDamage = Monster::calculateDamage() + 5;

	//Return total damage
    	return totDamage;
}
