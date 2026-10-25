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
2. The `json.hpp` header file is already included in the `include` folder. No extra download is needed.
3. **For Visual Studio users:** Open `Caristhe-Vera-Engine.sln` and press `F5`.
4. **For command line users:** Compile from the root directory:
   ```bash
   g++ src/main.cpp -o game -std=c++17
