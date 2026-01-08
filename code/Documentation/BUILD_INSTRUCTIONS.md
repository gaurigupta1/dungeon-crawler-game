# Build Instructions for RPG Dungeon Crawler

This document explains how to compile, run, and test the RPG Game.

---

### Verify Installation

```bash
# Check compiler
g++ --version

# Check make
make --version

# Check valgrind
valgrind --version
```

---

## Project Structure

```
starter_code/
├── Documentation
├──── README.md              # This file
├──── BUILD_INSTRUCTIONS.md  # How to compile and run
│
├── Makefile                 # Makefile for build system
│
├── bin
├──── dungeon_rpg.solution       # Fully compiled executable for testing and
│                              reference (will run on mario.ece.utexas.edu)
│
│
├── include
├──── Character.h            # Base character class
├──── Player.h               # Player class (inherits Character)
├──── Monster.h              # Monster hierarchy
├──── Item.h                 # Item hierarchy
├──── Room.h                 # Room class
├──── Game.h                 # Game controller
│
├── src
├──── Character.cpp          # Character class implementation
├──── Player.cpp             # Player class implementation
├──── Monster.cpp            # Monster classes implementation
├──── Item.cpp               # Item classes implementation
├──── Room.cpp               # Room class implementation
├──── Game.cpp               # Game controller implementation
└──── main.cpp               # Entry point
```

---

## Basic Build Commands

### Compile the Project

```bash
make
```

This will:
1. Compile all .cpp files into .o object files
2. Link object files into executable `dungeon_rpg` in the `bin/` directory
3. Display any compilation errors or warnings

**Expected output**:
```
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/main.cpp
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/Character.cpp
g++ -c -std=c++98 -Wall -Wextra -Werror -g src/Player.cpp
...
g++ -o bin/dungeon_rpg src/main.o src/Character.o src/Player.o src/Monster.o src/Item.o src/Room.o src/Game.o
```

### Run the Game

```bash
./bin/dungeon_rpg
```


### Clean Build Files

```bash
make clean
```

This removes all compiled object files (.o) and the executable, giving you a fresh start.

### Rebuild from Scratch

```bash
make clean
make
```

---

### Compiler Flags Explained

- `-std=c++98`: Use C++98 standard (compatible with older systems)
- `-Wall`: Enable all warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors (forces clean code)
- `-g`: Include debugging symbols (for gdb)

---

## Compilation Process

### Step-by-Step

1. **Preprocessing**: Expands #include directives
   ```bash
   g++ -E src/Character.cpp > src/Character.i
   ```

2. **Compilation**: Converts to assembly
   ```bash
   g++ -S src/Character.cpp
   ```

3. **Assembly**: Creates object file
   ```bash
   g++ -c src/Character.cpp -o src/Character.o
   ```

4. **Linking**: Combines object files into executable
   ```bash
   g++ -o bin/dungeon_rpg src/main.o src/Character.o src/Player.o ...
   ```

The Makefile automates all these steps!

---

## GDB Debugging guide

### Using GDB (GNU Debugger)

**Compile with debug symbols** (already done with -g flag):
```bash
make
```

**Run under debugger**:
```bash
gdb ./bin/dungeon_rpg
```

**GDB Commands**:
```
(gdb) run                    # Run program
(gdb) break main             # Set breakpoint at main
(gdb) break Game.cpp:50      # Set breakpoint at line 50
(gdb) next                   # Execute next line
(gdb) step                   # Step into function
(gdb) continue               # Continue execution
(gdb) print variable         # Print variable value
(gdb) backtrace              # Show call stack
(gdb) quit                   # Exit gdb
```

**Example debugging session**:
```bash
$ gdb ./bin/dungeon_rpg
(gdb) break main
Breakpoint 1 at 0x1234: file main.cpp, line 5.
(gdb) run
Starting program: ./bin/dungeon_rpg
Breakpoint 1, main () at main.cpp:5
(gdb) next
(gdb) print game
(gdb) continue
```

---

## Testing Strategy

### Week 1: Unit Testing

Created simple test programs for each class:

**test_character.cpp**:
```cpp
#include "Character.h"
#include <iostream>

int main() {
    Character hero("Hero", 100, 10, 5);
    hero.displayStats();
    hero.takeDamage(30);
    hero.heal(10);
    return 0;
}
```

**Compile and run**:
```bash
g++ -o test_character test_character.cpp Character.cpp
./test_character
```

### Week 2: Integration Testing

Tested class interactions:

**test_player_inventory.cpp**:
```cpp
#include "Player.h"
#include "Item.h"

int main() {
    Player p("Bob");
    p.addItem(new Weapon("Sword", "Sharp", 5));
    p.displayInventory();
    p.equipWeapon("sword");
    // ... more tests
    return 0;
}
```

### Week 3: System Testing

Tested the complete game:

1. **Functional tests**:
   - Can move between rooms?
   - Can pick up items?
   - Can fight monsters?
   - Can win game?

2. **Edge cases**:
   - What if player tries to go invalid direction?
   - What if player tries to pick up non-existent item?
   - What if player tries to use non-consumable?

3. **Memory tests**:
   ```bash
   valgrind --leak-check=full ./bin/dungeon_rpg
   ```
   Played through game and quit normally with zero leaks.

---

## Summary of Commands

```bash
# Build
make                    # Compile project
make clean              # Remove compiled files
make clean && make      # Clean rebuild

# Run
./bin/dungeon_rpg              # Run game

# Debug
gdb ./bin/dungeon_rpg          # Debug with GDB
valgrind --leak-check=full ./bin/dungeon_rpg  # Check memory leaks
```

---
