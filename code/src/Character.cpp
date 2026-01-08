#include "Character.h"
#include <cstdlib>

// Character constructor
// - Use initializer list to initialize all member variables
// - Set current_hp to hp (start at full health)
// - Set alive to true (character starts alive)
// - Format: Character::Character(params) : member1(value1), member2(value2) { }
//
Character::Character(const std::string& name, int hp, int attack, int defense)
    : name(name), max_hp(hp), current_hp(hp), attack(attack), 
      defense(defense), alive(true) {
}


// Character destructor
// - For base Character class, clean up any dynamic resources if needed
// - Add (and later remove) a debug print statement if helpful for tracking object lifetime
// - Example: std::cout << "Character " << name << " destroyed" << std::endl;
//
Character::~Character() {
}


// calculateDamage
// - Return attack damage plus a random bonus (0-4)
// - Use: rand() % 5 to get random number from 0 to 4
//
int Character::calculateDamage() const {
    // Calculate and return damage
    // Base damage is attack stat plus small random bonus

	//Use: rand() % 5 to get random number from 0 to 4
	int rando = rand() % 5;

	//Return attack damage plus a random bonus (0-4)
	rando += attack;
	return rando;
}


// takeDamage
// - Reduce damage by defense value (actual_damage = damage - defense)
// - Make sure actual damage is not negative (minimum 0)
// - Subtract actual damage from current_hp
// - If hp drops to 0 or below: set hp to 0 and set alive to false
// - Print damage message showing damage taken and remaining HP
// - Format: "Name takes X damage! (Y/Z HP)"
//
void Character::takeDamage(int damage) {
    // Calculate actual damage after defense

	//Reduce damage by defense value
	int actual_damage = damage - defense;

	//Make sure actual damage is not negative (minimum 0)
	if(actual_damage < 0){
		//if less than 0, print error message and return
		std::cout << "takeDamage Error" << std::endl;
		return;
	}

        //Apply damage to current_hp
	current_hp -= actual_damage;

        //Check if character died (hp <= 0)
	if(current_hp < 0){
		//set hp to 0 and set alive to false
		current_hp = 0;
		alive = false;
	}

	//Print damage message with remaining HP
	std::cout << name << " takes " << actual_damage << " damage! (" << current_hp << "/" << max_hp << " HP)" << std::endl;

}


// heal
// - Add healing amount to current_hp
// - Make sure current_hp doesn't exceed max_hp (cap at maximum)
// - Print healing message showing amount healed and current HP
// - Format: "Name heals X HP! (Y/Z HP)"
//
void Character::heal(int amount) {
        //Add amount to current_hp
	current_hp += amount;

	//Cap at max_hp
	if(current_hp > max_hp)
		current_hp = max_hp;

        //Print healing message
	std::cout << name << " heals " << amount << " HP! (" << current_hp << "/" << max_hp << " HP)" << std::endl;
}


// displayStats
// - Print character name and HP
// - Format: "Name [HP: current/max]"
// - This is the default implementation - derived classes can override
//
void Character::displayStats() const {
    // Print character stats
	std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]" << std::endl;
}


// displayStatus
// - Brief one-line status (used during combat)
// - Don't add newline at the end (combat system will add it)
// - Format: "Name [HP: current/max]"
//
void Character::displayStatus() const {
    // Print brief status (no newline)
	std::cout << name << " [HP: " << current_hp << "/" << max_hp << "]" << std::endl;
}
