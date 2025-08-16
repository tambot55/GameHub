#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

using namespace std;

// Inventory List
class Inventory {
    vector<string> items;
public:
    void addItem(const string& item) {
        items.push_back(item);
        cout << item << " added to inventory." << endl;
    }

    void showInventory() const {
        cout << "Inventory:" << endl;
        for (const string& item : items) {
            cout << "- " << item << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        for (const auto& item : items) {
            out << item << endl;
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        items.clear();
        ifstream in(filename);
        string item;
        while (getline(in, item)) {
            items.push_back(item);
        }
        in.close();
    }
};

// Undo Stack
class ActionStack {
    stack<string> actions;
public:
    void performAction(const string& action) {
        actions.push(action);
        cout << "Performed: " << action << endl;
    }

    void undoAction() {
        if (!actions.empty()) {
            cout << "Undo: " << actions.top() << endl;
            actions.pop();
        } else {
            cout << "No actions to undo." << endl;
        }
    }
};

// Player Stats
class PlayerStats {
    unordered_map<string, int> stats;
public:
    void setStat(const string& key, int value) {
        stats[key] = value;
    }

    void showStats() const {
        cout << "Player Stats:" << endl;
        for (auto& [key, value] : stats) {
            cout << key << ": " << value << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        for (const auto& [key, value] : stats) {
            out << key << " " << value << endl;
        }
        out.close();
    }

    void loadFromFile(const string& filename) {
        stats.clear();
        ifstream in(filename);
        string key;
        int value;
        while (in >> key >> value) {
            stats[key] = value;
        }
        in.close();
    }
};

// Skill Tree
class SkillNode {
public:
    string name;
    vector<SkillNode*> children;
    bool unlocked;

    SkillNode(const string& n) : name(n), unlocked(false) {}

    void addChild(SkillNode* child) {
        children.push_back(child);
    }

    SkillNode* find(const string& skill) {
        if (name == skill) return this;
        for (auto* child : children) {
            SkillNode* result = child->find(skill);
            if (result) return result;
        }
        return nullptr;
    }

    void display(int depth = 0) const {
        for (int i = 0; i < depth; ++i) cout << "--";
        cout << name << (unlocked ? " [Unlocked]" : "") << endl;
        for (SkillNode* child : children) {
            child->display(depth + 1);
        }
    }
};

class SkillTree {
    SkillNode* root;
public:
    SkillTree() {
        root = new SkillNode("Guardian");
        SkillNode* arc = new SkillNode("Arc Subclass");
        SkillNode* void_ = new SkillNode("Void Subclass");
        SkillNode* solar = new SkillNode("Solar Subclass");

        arc->addChild(new SkillNode("Arc Staff"));
        arc->addChild(new SkillNode("Blink"));

        void_->addChild(new SkillNode("Suppressor Grenade"));
        void_->addChild(new SkillNode("Devour"));

        solar->addChild(new SkillNode("Sunspot"));
        solar->addChild(new SkillNode("Radiant"));

        root->addChild(arc);
        root->addChild(void_);
        root->addChild(solar);
    }

    void displayTree() const {
        cout << "Skill Tree:" << endl;
        root->display();
    }

    void unlockSkill(const string& name) {
        SkillNode* node = root->find(name);
        if (node) {
            node->unlocked = true;
            cout << name << " has been unlocked." << endl;
        } else {
            cout << "Skill not found." << endl;
        }
    }
};

// Game Map with Pathfinding
class GameMap {
    map<string, set<string>> adj;
public:
    void addEdge(const string& u, const string& v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void showMap() const {
        cout << "Map Connections:" << endl;
        for (auto& [zone, neighbors] : adj) {
            cout << zone << " -> ";
            for (const auto& n : neighbors) {
                cout << n << " ";
            }
            cout << endl;
        }
    }

    void findPath(const string& start, const string& goal) {
        if (adj.find(start) == adj.end() || adj.find(goal) == adj.end()) {
            cout << "One or both zones not found on the map." << endl;
            return;
        }

        map<string, string> prev;
        queue<string> q;
        set<string> visited;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            if (current == goal) break;

            for (const string& neighbor : adj[current]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    prev[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        if (!prev.count(goal)) {
            cout << "No path found from " << start << " to " << goal << "." << endl;
            return;
        }

        vector<string> path;
        for (string at = goal; at != start; at = prev[at])
            path.push_back(at);
        path.push_back(start);
        reverse(path.begin(), path.end());

        cout << "Path from " << start << " to " << goal << ": ";
        for (const string& zone : path)
            cout << zone << (zone == goal ? "\n" : " -> ");
    }
};

// Main Program
int main() {
    Inventory inv;
    ActionStack undoSystem;
    PlayerStats stats;
    SkillTree skills;
    GameMap map;

    map.addEdge("Tower", "EDZ");
    map.addEdge("Tower", "Crucible");
    map.addEdge("EDZ", "Moon");
    map.addEdge("Moon", "Europa");

    // Load from files
    inv.loadFromFile("inventory.txt");
    stats.loadFromFile("stats.txt");

    int choice;
    string input;

    while (true) {
        cout << "\n--- Destiny 2 Hub ---" << endl;
        cout << "1. Add item to Inventory" << endl;
        cout << "2. Show Inventory" << endl;
        cout << "3. Perform Action" << endl;
        cout << "4. Undo Action" << endl;
        cout << "5. Show Player Stats" << endl;
        cout << "6. Set Player Stat" << endl;
        cout << "7. Display Skill Tree" << endl;
        cout << "8. Unlock Skill" << endl;
        cout << "9. Show Game Map" << endl;
        cout << "10. Find Path Between Zones" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid option. Please enter a number between 0 and 10." << endl;
            continue;
        }

        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter item: ";
                getline(cin, input);
                inv.addItem(input);
                break;
            case 2:
                inv.showInventory();
                break;
            case 3:
                cout << "Enter action: ";
                getline(cin, input);
                undoSystem.performAction(input);
                break;
            case 4:
                undoSystem.undoAction();
                break;
            case 5:
                stats.showStats();
                break;
            case 6: {
                string statName;
                int statValue;
                cout << "Enter stat name (e.g. Power): ";
                getline(cin, statName);
                cout << "Enter value: ";
                while (!(cin >> statValue)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a valid number: ";
                }
                cin.ignore();
                stats.setStat(statName, statValue);
                cout << statName << " set to " << statValue << "." << endl;
                break;
            }
            case 7:
                skills.displayTree();
                break;
            case 8:
                cout << "Enter skill to unlock: ";
                getline(cin, input);
                skills.unlockSkill(input);
                break;
            case 9:
                map.showMap();
                break;
            case 10: {
                string start, end;
                cout << "Start zone: ";
                getline(cin, start);
                cout << "End zone: ";
                getline(cin, end);
                map.findPath(start, end);
                break;
            }
            case 0:
                inv.saveToFile("inventory.txt");
                stats.saveToFile("stats.txt");
                cout << "Exiting Destiny 2 Hub. Inventory and stats saved." << endl;
                return 0;
            default:
                cout << "Invalid option. Please enter a number between 0 and 10." << endl;
        }
    }

    return 0;
}
