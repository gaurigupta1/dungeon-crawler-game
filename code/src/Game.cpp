#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// Game destructor
Game::~Game() {
    // Clean up player and all rooms

	//if player exists
	if(player != NULL){
		//delete player
		delete player;
	}

	//iterate through map
	for (std::map<std::string, Room*>::iterator it = world.begin(); it != world.end(); ++it){
		delete it->second;
	}

	//clear the world
	world.clear();

}


// initializeWorld
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // Create rooms
    // Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");

	//create the new rooms
	Room* entrance = new Room("Entrance", "A dark stone corridor");
	Room* hallway = new Room("Hallway", "A dark stone corridor");
	Room* armory = new Room("Armory", "Armor everywhere");
	Room* treasury = new Room("Treasury", "Treasure everywhere");
	Room* throneRoom = new Room("Throne Room", "The Dragon Boss Grand Room!");

    // Add rooms to world using addRoom
	addRoom(entrance);
	addRoom(hallway);
	addRoom(armory);
	addRoom(treasury);
	addRoom(throneRoom);

    // Connect rooms bidirectionally
	connectRooms("Hallway", "north", "Throne Room");
	connectRooms("Hallway", "south", "Entrance");
	connectRooms("Hallway", "east", "Treasury");
	connectRooms("Hallway", "west", "Armory");

    // Add monsters
	hallway->setMonster(new Goblin());
	armory->setMonster(new Skeleton());
	treasury->setMonster(new Skeleton());
	throneRoom->setMonster(new Dragon());

    // Add items
	entrance->addItem(new Consumable("Small Potion", "Restores 10 HP", 10));
	armory->addItem(new Weapon("Iron Sword", "A sturdy blade", 5));
	armory->addItem(new Armor("Chain Mail", "Protective armor", 3));
	treasury->addItem(new Consumable("Health Potion", "Restores health", 30));

    // Set starting room
	current_room = entrance;
}


// createStartingInventory
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // Give player starting items
	// - Give player starting weapon: Rusty Dagger (damage +2)
	player->addItem(new Weapon("Rusty Dagger", "Does minor damage", 2));

	// - Give player starting food: Bread (heals 5 HP)
	player->addItem(new Consumable("Bread", "A hearty food", 5));
}


// addRoom
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // Add room to world map

	//if room ptr is not null
	if(room != NULL){
		//add room to world map using room's name as key
		world[room->getName()] = room;
	}
}


// connectRooms
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // Connect rooms bidirectionally

        //iterate through world map to find rooms
        std::map<std::string, Room*>::const_iterator it1 = world.find(room1_name);
        std::map<std::string, Room*>::const_iterator it2 = world.find(room2_name);

	//make sure both rooms exist
	if (it1 == world.end() || it2 == world.end()) {
		std::cout << "Error: one or both rooms not found" << std::endl;
		return;
	}

        //store room pointers
        Room* room1 = it1->second;
        Room* room2 = it2->second;

	//add forward direction (room1 to room2)
	room1->addExit(direction, room2);

	//find reverse direction
	std::string reverse = "";
	if(direction == "north") {reverse = "south";}
	else if(direction == "south") {reverse = "north";}
	else if(direction == "east") {reverse = "west";}
	else if(direction == "west") {reverse = "east";}

	//make sure reverse if not empty
	if(reverse != ""){
		room2->addExit(reverse, room1);
	} else {
		//if reverse is empty, print error message
		std::cout << "Error: reverse direction not found" << std::endl;
	}
}


// run - main game loop
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop:
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // Implement main game loop

	//print Welcome Message
	std::cout << std::endl << "=== DUNGEON CRAWLER RPG ===" << std::endl;

	//Get player name from input
	std::string playerName = "";
	std::cout << "Enter your name, brave adventurer: ";
	std::getline(std::cin, playerName);

	//Create Player
	player = new Player(playerName);

	//Call initializeWorld()
	initializeWorld();

	//Call createStartingInventory()
	createStartingInventory();

	//display welcome and help messages
	std::cout << std::endl;
	std::cout << "Welcome, " << playerName << "!" << std::endl;
	std::cout << "Your quest: Defeat the dragon in the throne room!" << std::endl;
	std::cout << "Type 'help' for commands." << std::endl;

	//Display starting room
	current_room->display();

	//MAIN GAME LOOP
	//while game is nont over
	while(!game_over){
		//print prompt
		std::cout << " > ";

		//Get command
		std::string command = "";
		std::getline(std::cin, command);

		//Convert to lowercase
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);

		//Call processCommand()
		processCommand(command);

		//Check defeat condition (player dead)
		if(!player->isAlive()){
			std::cout << "You have died. Game Over!" << std::endl;
			game_over = true;

		//Check victory condition
		} else if(victory == true){
			std::cout << "VICTORY! WOU WIN!!!" << std::endl;
			game_over = true;
		}


	}
}


// processCommand
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // Parse and dispatch command

	//use istringstream to extract parts of command
	std::istringstream separate(command);

	//string to parse command to verb
	std::string verb;

	//parse command to verb, if empty, return
	if(!(separate >> verb)) {
		return;
	}

	//string to parse remaining part of command to object
	std::string object;

	//parse remainder to object
	std::getline(separate, object);

	// Trim leading spaces from object

	//find first not space character
	std::size_t start = object.find_first_not_of(" \t");

	//get rid of the leading spaces
	if(start != std::string::npos){
	        object = object.substr(start);
	} else {
		object.clear();
	}

	//Dispatch based on verb

	//if verb is "go" or "move"
	if(verb == "go" || verb == "move") {
		//if object exists
        	if (!object.empty()) {
			//move object
        		move(object);
		//otherwise
        	} else {
			//error message
        		std::cout << "Error: empty object" << std::endl;
        	}

	//if verb is "look" of "l"
	} else if (verb == "look" || verb == "l") {
		//call look
        	look();
	}

	//if verb is "attack" or "fight"
	else if (verb == "attack" || verb == "fight") {
        	attack();
	}

	//if verb is "pickup" or "get" or "take"
	else if (verb == "pickup" || verb == "get" || verb == "take") {
		//if object exists
        	if (!object.empty()) {
			//pick up object
        		pickupItem(object);
		//otherwise
        	} else {
			//error message
        		std::cout << "Error: object does not exist." << std::endl;
        	}
	}

	//if verb is "inventory" or "i"
	else if (verb == "inventory" || verb == "i") {
		//call inventory
        	inventory();
	}

	//if verb is "use"
	else if (verb == "use") {
		//if object exists
        	if (!object.empty()) {
			//use object
        		useItem(object);
		//otherwise
        	} else {
			//error message
        		std::cout << "Error: object does not exist." << std::endl;
        	}
	}

	//if verb is "equip" or "e"
	else if (verb == "equip" || verb == "e") {
        	if (!object.empty()) {
        		equip(object);
        	} else {
        		std::cout << "Error: object does not exist." << std::endl;
        	}
	}

	//if verb is "stats"
	else if (verb == "stats") {
		//display stats of player
        	player->displayStats();
	}

	//if verb is "help" or "h" or "?"
	else if (verb == "help" || verb == "h" || verb == "?") {
		//call help
	        help();
	}

	//if verb is "quit" or "exit"
	else if (verb == "quit" || verb == "exit") {
		//print message and leave by setting game_over to true
        	std::cout << "Exiting game..." << std::endl;
        	game_over = true;
	}

	//Command doesn't exist, print error message
	else {
        	std::cout << "Error: Command does not exist." << std::endl;
	}

}


// move() function
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // Move to adjacent room

	//if monster is in the room
	if(current_room->hasMonster()){
		//path is blocked. print message and return
		std::cout << "You cannpt leave while a monster blocks your path!" << std::endl;
		return;
	}

	//Get exit in specified direction
	Room* exit = current_room->getExit(direction);

	//If exit exists:
	if(exit){
		//Update current_room
		current_room = exit;

		//Display new room
		current_room->display();

		//Mark as visited
		current_room->markVisited();
	}

	//Otherwise print error message
	else {
		std::cout << "You can't go that way!" << std::endl;
	}
}


// look() function
// - Simply display current room
//
void Game::look() {
    // Display current room
	current_room->display();
}


// attack() function
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // Attack monster in room

	//Check if monster in room
	if(current_room->hasMonster()){
		//If monster present, call combat()
		combat(current_room->getMonster());
	} else {
		//If no monster, print message and return
		std::cout << "Error, no monster present!" << std::endl;
	}

}


// combat
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // turn-based combat

	//Print "=== COMBAT BEGINS ==="
	std::cout << "=== COMBAT BEGINS ===" << std::endl;

	//Combat loop: while both player and monster are alive
	while(player->isAlive() && monster->isAlive()){

		//Prompt for player action: attack/use <item>/flee
		std::string action = "";
		std::cout << "Your turn, enter an action: ";
		std::getline(std::cin, action);

		//make action lowercase
		std::transform(action.begin(), action.end(), action.begin(), ::tolower);

                //for use condition, exctract use
                std::string sub = action.substr(0,3);

		//if attack
		if(action == "attack"){
			//Calculate player damage
			int playerDamage = player->calculateDamage();

			//Monster takes damage
			std::cout << "========================================" << std::endl;
			monster->takeDamage(playerDamage);
			std::cout << std::endl;

			//if monster is dead
			if(!monster->isAlive()){
				//Print victory
				std::cout << "VICTORY! You defeated " << monster->getName() << "!" << std::endl;

				//Player gains exp and gold
				player->gainExperience(monster->getExperienceReward());
				player->addGold(monster->getGoldReward());

				//Get loot from monster
				std::vector<Item*> getLoot = monster->dropLoot();

				//Add loot to current room
				for(int i = 0; i < (int)getLoot.size(); i++){
					//add each loot item from loot table to toom items
					current_room->addItem(getLoot[i]);
				}

				//Check if Dragon
				if(monster->getName() == "Dragon"){
					//if Dragon, player won the game, victory = true
					victory = true;
				}

				//Clear monster from room
				current_room->clearMonster();

				//Break from loop
				break;

			}
		}

		//if use
		else if(sub == "use"){
			//Parse and call use Item with processCommand
			std::cout << "========================================" << std::endl;
			processCommand(action);
			std::cout << std::endl;
		}

		//if flee
		else if(action == "flee"){
			//print message
			std::cout << "Fleeing from combat..." << std::endl;

			//break from loop
			break;
		}

		//Monster's turn
		//print monster attack message
		std::cout << monster->getAttackMessage() << std::endl;

		//calculate monster damage
		int monstDamage = monster->getAttack();

		//player takes damage
		player->takeDamage(monstDamage);
		std::cout << "========================================" << std::endl;
	}

	//Print "=== COMBAT ENDS ==="
	std::cout << "=== COMBAT ENDS ===" << std::endl;
}


// pickupItem
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // Pick up item from room

	//Get item from current room
	Item* pickup = current_room->getItem(item_name);

	//if exists:
	if(pickup){
		//Add to player inventory
		player->addItem(pickup);

		//Remove from room (ownership transfer!)
		current_room->removeItem(item_name);
	} else {
		//Otherwise print error
		std::cout << "Error: item not found." << std::endl;
	}
}


// inventory
//
void Game::inventory() {
    // Display player inventory
	player->displayInventory();
}


// useItem
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // Use item from inventory
	player->useItem(item_name);
}


// equip
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // Equip weapon or armor

	//Get item from player inventory
	Item* equipItem = player->getItem(item_name);

	//Check if item exists
	if(equipItem){
		//If "Weapon"
		if(equipItem->getType() == "Weapon") {
			//call player->equipWeapon()
			player->equipWeapon(equipItem->getName());

		//If "Armor"
		} else if(equipItem->getType() == "Armor") {
			//call player->equipArmor()
			player->equipArmor(equipItem->getName());

		//otherwise
		} else {
			//print error message
			std::cout << "Can't equip item. Your item type is: " << equipItem->getType() << std::endl;
		}

	//if item isn't in inventory
	} else {
		//print error message
		std::cout << "Error: item not present in inventory." << std::endl;
	}

}


// help() function
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // Display help message

	//Print all available commands with descriptions
        std::cout << "========================================" << std::endl;
	std::cout << "Commands:" << std::endl;
	std::cout << " * go <direction> - Move" << std::endl;
	std::cout << " * look - Look around" << std::endl;
	std::cout << " * attack - Attack monster" << std::endl;
	std::cout << " * pickup <item> - Pick up item" << std::endl;
	std::cout << " * inventory - Show inventory" << std::endl;
	std::cout << " * use <item> - Use consumable" << std::endl;
	std::cout << " * equip <item> - Equip weapon/armor" << std::endl;
	std::cout << " * stats - Show character stats" << std::endl;
	std::cout << " * help - Show this help" << std::endl;
	std::cout << " * quit - Exit game" << std::endl;
	std::cout << "========================================" << std::endl;

}
