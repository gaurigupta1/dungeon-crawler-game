#include "Item.h"

// ============================================================================
// Base Item class implementation
// ============================================================================

// Item constructor
// - Use initializer list to initialize all member variables
// - Parameters map directly to member variables
//
Item::Item(const std::string& name, const std::string& description,
           const std::string& type, int value)
    : name(name), description(description), type(type), value(value) {
}


// Item destructor
// - Can add debug output if helpful
//
Item::~Item() {
}


// displayInfo (base version)
// - Print item name, description, and value
// - Format:
//   [ITEM] ItemName
//     Description text
//     Value: X
//
void Item::displayInfo() const {
    // Display item information

	//print object type + name
	std::cout << "[ITEM] " << name << std::endl;

	//print description
	std::cout << "  " << description << std::endl;

	//print value
	std::cout << "  Value: " << value << std::endl;
}


// displayBrief
// - One line format: "Name (Type)"
// - Example: "Iron Sword (Weapon)"
//
void Item::displayBrief() const {
    // Display brief item info

	//print name and type
	std::cout << name << " (" << type << ")" << std::endl;
}


// ============================================================================
// Weapon class implementation
// ============================================================================

// Weapon constructor
// - MUST call base Item constructor using initializer list
// - Type should be "Weapon"
// - Value is the damage bonus
// - Also initialize damage_bonus member
// - Format: Weapon::Weapon(...) : Item(name, desc, "Weapon", damage), damage_bonus(damage) { }
//
Weapon::Weapon(const std::string& name, const std::string& description, int damage)
    : Item(name, description, "Weapon", damage), damage_bonus(damage) {
}


// Override displayInfo for Weapon
// - Print weapon-specific format
// - Use getName(), getDescription(), getDamageBonus()
// - Format:
//   [WEAPON] WeaponName
//     Description
//     Damage Bonus: +X
//
void Weapon::displayInfo() const {
    // Display weapon-specific information

	//print type + name
	std::cout << "[WEAPON] " << getName() << std::endl;

	//print description
	std::cout << "  " << getDescription() << std::endl;

	//print damage bonus
	std::cout << "  Damage Bonus: +" << getDamageBonus() << std::endl;
}


// ============================================================================
// Armor class implementation
// ============================================================================

//  Armor constructor
// - MUST call base Item constructor using initializer list
// - Type should be "Armor"
// - Value is the defense bonus
// - Also initialize defense_bonus member
//
Armor::Armor(const std::string& name, const std::string& description, int defense)
    : Item(name, description, "Armor", defense), defense_bonus(defense) {
}


// Override displayInfo for Armor
// - Print armor-specific format
// - Format:
//   [ARMOR] ArmorName
//     Description
//     Defense Bonus: +X
//
void Armor::displayInfo() const {
    // Display armor-specific information

	//print type and name
	std::cout << "[ARMOR] " << getName() << std::endl;

	//print description
        std::cout << "  " << getDescription() << std::endl;

	//print defense bonus
        std::cout << "  Defense Bonus: +" << getDefenseBonus() << std::endl;
}


// ============================================================================
// Consumable class implementation
// ============================================================================

// Consumable constructor
// - MUST call base Item constructor using initializer list
// - Type should be "Consumable"
// - Value is the healing amount
// - Initialize healing_amount and set used to false
//
Consumable::Consumable(const std::string& name, const std::string& description, 
                       int healing)
    : Item(name, description, "Consumable", healing), 
      healing_amount(healing), used(false) {
}


// Override displayInfo for Consumable
// - Print consumable-specific format
// - Format:
//   [CONSUMABLE] ConsumableName
//     Description
//     Restores: X HP
//
void Consumable::displayInfo() const {
    // Display consumable-specific information

	//print type and name
	std::cout << "[CONSUMABLE] " << getName() << std::endl;

	//print description
	std::cout << "  " << getDescription() << std::endl;

	//print healing amount
	std::cout << "  Restores: " << getHealingAmount() << " HP" << std::endl;
}


// use() function
// - Check if already used
// - If not used: print message and set used to true
// - If already used: print error message
// - Format: "Used ItemName! Restored X HP."
//
void Consumable::use() {
    // Implement use logic

	//Check if already used
	if(isUsed() == true){
		//If already used: print error message
		std::cout << "Error: " << getName() << " already used!" << std::endl;
	//otherwise
	} else {
		//use item (used = true)
		used = true;

		//print success message
		std::cout << "Used " << getName() << "! Restored " << getHealingAmount() << " HP." << std::endl;
	}
}
