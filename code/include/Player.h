#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Item.h"
#include <vector>

/**
 * Player class - Represents the player character
 * 
 * Inherits from Character and adds:
 * - Leveling system (experience and levels)
 * - Inventory management
 * - Equipment system (weapons and armor)
 * - Gold currency
 * 
 * MY LEARNING OBJECTIVES:
 * - Practice inheritance
 * - Override base class methods
 * - Manage complex object relationships
 * - Handle vectors of pointers properly
 */
class Player : public Character {
private:
    int level;
    int experience;
    int gold;
    std::vector<Item*> inventory;  // Player owns these items!
    Item* equipped_weapon;         // Points to item in inventory (not separately owned)
    Item* equipped_armor;          // Points to item in inventory (not separately owned)
    
public:
    // Constructor
    // in Player.cpp
    // Must call Character base constructor
    Player(const std::string& name);
    
    // Destructor - CRITICAL for memory management!
    // in Player.cpp
    // Must delete all items in inventory
    virtual ~Player();
    
    // Override displayStats from Character
    // in Player.cpp
    void displayStats() const;
    
    // Override calculateDamage to include weapon bonus
    // in Player.cpp
    int calculateDamage() const;
    
    // Inventory management
    // in Player.cpp
    void addItem(Item* item);
    void removeItem(const std::string& item_name);
    void displayInventory() const;
    bool hasItem(const std::string& item_name) const;
    Item* getItem(const std::string& item_name);
    
    // Equipment management
    // in Player.cpp
    void equipWeapon(const std::string& weapon_name);
    void equipArmor(const std::string& armor_name);
    void unequipWeapon();
    void unequipArmor();
    
    // Use consumable item from inventory
    // in Player.cpp
    void useItem(const std::string& item_name);
    
    // Level and experience
    // in Player.cpp
    void gainExperience(int exp);
    void levelUp();
    
    // Getters
    int getLevel() const { return level; }
    int getExperience() const { return experience; }
    int getGold() const { return gold; }
    
    // Gold management
    void addGold(int amount) { gold += amount; }
    void spendGold(int amount) { gold -= amount; }
};

#endif // PLAYER_H
