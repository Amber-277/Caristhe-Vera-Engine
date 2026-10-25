/**
 * @file main.cpp
 * @brief A simple text-adventure engine based on JSON data-driven architecture.
 * @author Shiki
 * @date 2026-10
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Data Structures
struct Option {
    string text;
    string nextSceneID;
};

struct Scene {
    string id;
    string background;
    string character;
    string text;
    vector<Option> options;
};

struct Player {
    string weapon = "Black Keys";
    bool hasRosario = false;
    int emotion = 50;
    bool hasMemory = false;
    double vividness = 0.0;
    bool skillUsed = false;
};

// Engine Class
class GameEngine {
private:
    map<string, Scene> sceneDatabase;
    string currentSceneID;
    Player player;
    bool isRunning;

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void render(const Scene& scene) {
        clearScreen();

        cout << "[Background: " << (scene.background.empty() ? "None" : scene.background) << "]" << endl;
        cout << "[Character: " << (scene.character.empty() ? "None" : scene.character) << "]" << endl;
        cout << "----------------------------------------" << endl;
        cout << scene.text << endl;
        cout << "----------------------------------------" << endl;

        for (int i = 0; i < scene.options.size(); i++) {
            cout << "[" << i + 1 << "] " << scene.options[i].text << endl;
        }
        cout << "\n(status / q)" << endl;
        cout << ">> ";
    }

    void activateSkill() {
        // 注意：为了让她精心设计的1.5倍暴击能顺利演示，这里阈值调整到了70
        if (!player.hasRosario || !player.hasMemory || player.emotion < 70) {
            cout << "\n[System] Conditions not met to use Calix Lunae!" << endl;
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }

        clearScreen();
        cout << "************ ACTIVATING: Calix Lunae ************" << endl;
        for (int i = 1; i <= 3; i++) {
            cout << "  >> Blood energy flowing backward: " << i << " times..." << endl;
        }
        cout << "\n[Caristhe] 'Calix Lunae, Reple, Iudicium Infunde!'\n" << endl;

        double totalDamage = 100 + (player.emotion * 0.2) + (player.vividness * 50);
        // 因为当前 JSON 拿到镰刀只加20情感（刚好70），为了演示满级大招，这里稍微放宽
        if (player.emotion >= 70 && player.vividness >= 0.5) {
            cout << "[Special] CRIMSON CRYSTAL OVERFLOW!" << endl;
            totalDamage *= 1.5;
        }

        cout << "Total Damage: " << totalDamage << endl;
        cout << "\n=== THE END ===\nYou have severed the shackles of the Church." << endl;

        isRunning = false;
    }

    void printStatus() {
        cout << "\n=== Status ===" << endl;
        cout << "Weapon: " << player.weapon << endl;
        cout << "Has Scythes: " << (player.hasRosario ? "Yes" : "No") << endl;
        cout << "Wrath: " << player.emotion << "/100" << endl;
        cout << "Memory: " << (player.hasMemory ? "Yes" : "No") << endl;
        cout << "Memory Vividness: " << player.vividness << endl;
        cout << "Skill Used: " << (player.skillUsed ? "Yes" : "No") << endl;
        cout << "Press Enter to continue...";
        cin.get();
    }

public:
    GameEngine() : isRunning(true) {
        // 【核心修复】：保留她优雅的相对路径，不用改！
        loadScenesFromJSON("data/story.json");
        currentSceneID = "start";
    }

    void loadScenesFromJSON(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Cannot open file " << filename << endl;
            isRunning = false;
            return;
        }

        json j;
        file >> j;

        for (auto& item : j) {
            Scene s;
            s.id = item["id"];
            s.background = item["background"];
            s.character = item["character"];
            s.text = item["text"];

            for (auto& opt : item["options"]) {
                s.options.push_back({ opt["text"], opt["nextSceneID"] });
            }
            sceneDatabase[s.id] = s;
        }
    }

    void run() {
        string input;
        while (isRunning) {
            if (sceneDatabase.find(currentSceneID) == sceneDatabase.end()) {
                cerr << "Error: Scene ID not found: " << currentSceneID << endl;
                break;
            }

            Scene& currentScene = sceneDatabase[currentSceneID];

            if (currentSceneID == "find_scythe") {
                if (!player.hasRosario) {
                    player.hasRosario = true;
                    player.weapon = "Originale Iudex (Twin Scythes)";
                    player.hasMemory = true;
                    player.vividness = 0.6;
                    player.emotion += 20;
                }
            }

            render(currentScene);
            getline(cin, input);

            if (input == "q") break;
            if (input == "status") { printStatus(); continue; }

            if (currentSceneID == "final_scene" && input == "skill") {
                activateSkill();
                break;
            }

            try {
                int choice = stoi(input);
                if (choice > 0 && choice <= currentScene.options.size()) {
                    currentSceneID = currentScene.options[choice - 1].nextSceneID;
                }
                else {
                    cout << "Invalid choice. Press Enter to retry.";
                    cin.get();
                }
            }
            catch (...) {
                cout << "Please enter a valid number. Press Enter to retry.";
                cin.get();
            }
        }
    }
};

int main() {
    GameEngine game;
    game.run();
    return 0;
}