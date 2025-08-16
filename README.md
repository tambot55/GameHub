# GameHub
This is a C++ project that simulates a basic game hub, using Destiny 2 as reference.

## Features 
- Inventory System
- Undo Actions
- Player Stats
- Player Skills/Skill Tree
- World Map Navigation with Pathfinding
- Built for VS Code 

Language: C++
Build: g++, MinGW/MSYS2
IDE: Visual Studio Code

## How to Build/Run 

### Build in Terminal
```bash
g++ gamehub.cpp -o gamehub.exe
```
### Run
```bash
.\gamehub.exe
```
Or use Ctrl+Shift+B to build, and F5 to run. 

## Project Structure 
GAMEHUB/
├── .vscode/        # VS Code build/run configs  
|   ├── launch.json  
|   └── tasks.json   
├── .gitignore  
├── gamehub.cpp     # Main implementation  
├── inventory.txt   # Inventory data file  
├── README.md  
├── skills.txt      # Player skills data file  
└── stats.txt       # Player stats data file  
  

