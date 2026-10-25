# Caristhe Vera - The Heretic Saint (Engine Prototype)

A lightweight, text-based adventure game engine written in C++17, driven by external JSON data.

## 📖 About the Project
This is my first personal C++ project. Instead of hardcoding the story directly into the source code, I built a basic "State Machine" architecture.

The engine reads scene data (text, options, backgrounds, characters) from a `story.json` file. This means the game logic and the narrative data are completely decoupled.

The initial story is a dark fantasy narrative based on my original character, **Caristhe Vera**, a betrayed saint hunting the sins of the Church.

## 🛠️ Tech Stack & Architecture
- **Language:** C++ (Standard: C++17)
- **Data Parsing:** [nlohmann/json](https://github.com/nlohmann/json) (Single-header library)
- **Core Concept:** Finite State Machine (FSM), Data-Driven Design.

## 🚀 How to Run
1. Clone the repository to your local machine.
2. Download the `json.hpp` header file from the [official repository](https://github.com/nlohmann/json/releases) and place it in the root directory. *(Required for JSON parsing)*
3. Compile the `main.cpp` using any C++ compiler (e.g., GCC, Clang, or MSVC).
   ```bash
   g++ main.cpp -o game -std=c++17
   4.Run the compiled executable (or press F5 in Visual Studio).

Type 1 or 2 to make choices.

Type status to check player attributes.

Type skill to unleash the final attack (when conditions are met).
