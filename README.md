# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally

* cmake >= 3.7

  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)

  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0

  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)

  > Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
  >
* gcc/g++ >= 5.4

  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## CPP Snake Game - Enhanced Version

### New Features & Enhancements

Below are the **new features** added along with the **files modified** and  **expected behavior** :

#### 1. Register and Save Highscore

* **Files Modified:** `game.h`, `game.cpp`, `main.cpp`
* **Feature:** Allows players to enter their names and records high scores.
* **Implementation:**
  * Reads high score from a file if it exists.
  * If no file exists, it creates one and saves the player's score.
  * Ensures scores persist between game sessions.
* **Rubric Criteria Addressed:**
  * ✅ Reads and writes data to a file.
  * ✅ Uses file I/O to store high scores.

#### 2. Exit Game with Escape Button

* **Files Modified:** `controller.cpp`
* **Feature:** Enables the player to exit the game by pressing the **Escape (ESC)** key.
* **Implementation:**
  * Modified the `switch` case statement in `Controller::HandleInput` to detect  **ESC key press** .
* **Rubric Criteria Addressed:**
  * ✅ Accepts user input and processes it.

#### 3. Add Wall Obstacle

* **Files Modified:** `render.cpp`, `snake.h`, `snake.cpp`, `game.h`, `game.cpp`
* **Feature:** Introduces **static obstacles** that the snake must avoid.
* **Implementation:**
  * Walls are rendered as **fixed obstacles** on the grid.
  * If the snake collides with a wall, the game ends.
* **Rubric Criteria Addressed:**
  * ✅ Uses **control structures** (`if` conditions) to handle collisions.
  * ✅ Adds  **new game mechanics** .

#### 4. Pause and Resume Game

* **Files Modified:** `controller.h`, `controller.cpp`, `game.h`, `game.cpp`
* **New File Added:** `type.hpp` (defines `enum class SystemState`)
* **Feature:** Players can pause and resume the game using the  **Space Bar** .
* **Implementation:**
  * A **pause state** is added to the game logic.
  * The game loop checks if the state is paused before updating the game.
  * **Modified the `switch` case statement in `Controller::HandleInput`** to toggle between **pause and resume states** when the **Space Bar** is pressed.
  * **Pass-by-reference (`SystemState&`)** is used in the `Update` function to handle the game state efficiently.
* **Rubric Criteria Addressed:**
  * ✅ Accepts and processes new user inputs.
  * ✅ Uses **enumeration (`enum class`)** for better state management.
  * ✅ Uses  **control structures (switch-case) to handle pause/resume functionality** .
  * ✅ Uses **pass-by-reference (`State&`)** in `Game::Update` function.

#### 5. Create Food Class

* **Files Modified:** `game.h`, `game.cpp`, `snake.h`, `snake.cpp`, `renderer.h`, `renderer.cpp`
* **New File Added:** `food.h`, `food.cpp`
* **Feature:** Isolates the **food logic** into its own class.
* **Implementation:**
  * The food's position and rendering logic are handled by a dedicated class.
  * This allows easy future extensions like  **power-ups or multiple food types** .
* **Rubric Criteria Addressed:**
  * ✅ Uses **Object-Oriented Programming** (new class with attributes & methods).
  * ✅ Improves  **code organization and abstraction** .

#### 6. Use Initializer List in Snake Class

* **Files Modified:** `snake.h`
* **Feature:** Optimizes **snake class** using  **member initialization lists** .
* **Implementation:**
  * Instead of assigning values inside the constructor body, variables are initialized in the  **initializer list** .
* **Rubric Criteria Addressed:**
  * ✅ Uses **member initialization lists** for efficient memory handling.

#### 7. Implement Multi-Threaded Window Title Update with Mutex Locking

* **Files Modified:** `game.h`, `game.cpp`
* **Feature:** Uses **multi-threading** to update the window title  **without affecting game performance** , with **mutex synchronization** to prevent race conditions.
* **Implementation:**
  * A **separate thread** updates the window title every second.
  * A **std::mutex** is used to ensure only one thread updates the title at a time.
  * **std::unique_lock** is used to manage thread synchronization.
  * **Pass-by-reference (`std::string&`)** is used in `UpdateWindowTitle` to prevent unnecessary string copying.
* **Rubric Criteria Addressed:**
  * ✅ Implements  **multi-threading** .
  * ✅ Uses **std::mutex and std::unique_lock** to synchronize threads.
  * ✅ Ensures thread safety in concurrent execution.
  * ✅ Uses **pass-by-reference (`Renderer&`)** in `Game::UpdateWindowTitle`.

#### 8. Implement A* Algorithm for Pathfinding

* **Files Modified:** `AStar.h`, `AStar.cpp`
* **Feature:** Implements  **A* pathfinding* * for the snake to find the shortest route to food.
* **Implementation:**
  * The `AStar` class was created to:
    * Calculate the optimal path from the snake's head to the nearest food.
    * Return a vector of directions for the snake to follow.
  * This feature is **not fully complete yet** but lays the groundwork for AI-assisted movement.
* **Rubric Criteria Addressed:**
  * ✅ Uses **Object-Oriented Programming** (new `AStar` class).
  * ✅ Implements **control structures** (loops for pathfinding).
  * ✅ Uses  **vectors to store computed paths** .

#### 9. Refactor Snake and Food Handling to Use Shared Pointers

* **Files Modified:** `game.h`, `game.cpp`, `snake.h`, `snake.cpp`, `food.h`, `food.cpp`
* **Feature:** Uses **`std::shared_ptr`** to manage `Snake` and `Food` instances safely.
* **Implementation:**
  * Eliminates manual memory management.
  * Prevents **memory leaks** and improves  **automatic cleanup** .
* **Rubric Criteria Addressed:**
  * ✅ Uses  **smart pointers (`std::shared_ptr`) instead of raw pointers** .
  * ✅ Improves  **memory safety and efficiency** .

#### 10. Apply Rule of 5 to Renderer Class

* **Files Modified:** `renderer.h`, `renderer.cpp`
* **Feature:** Implements **Rule of 5** in the `Renderer` class.
* **Implementation:**
  * Defined the  **copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor** .
  * Ensures safe memory management for dynamic allocations.
* **Rubric Criteria Addressed:**
  * ✅ Follows **Rule of 5** for proper resource management.
  * ✅ Ensures  **deep copies and proper object transfers**.

---

### Rubric Criteria Summary

| **Category**                    | **Criteria Addressed**                                                                                                             |
| ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| **Loops, Functions, I/O**       | ✅ File I/O for high scores, ✅ Accepts and processes user input, ✅ Uses control structures (collision handling, pause state)           |
| **Object-Oriented Programming** | ✅ Encapsulated Food class, ✅ Member initialization list, ✅ A* Algorithm class for AI pathfinding                                      |
| **Memory Management**           | ✅ Used `std::shared_ptr`, ✅ Applied **Rule of 5** , ✅ Destructor ensures memory cleanup, ✅ Used **pass-by-reference** |
| **Concurrency**                 | ✅ Multi-threaded window title update with `std::mutex`, ✅ Uses `std::unique_lock`for thread synchronization                        |

## CC Attribution-ShareAlike 4.0 International

Shield: [CC BY-SA 4.0][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[CC BY-SA 4.0][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
