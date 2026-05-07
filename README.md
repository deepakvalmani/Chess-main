# ♟️ Chess Game – Object Oriented Programming Project

A complete Chess game developed in **C++** using **SFML 3.0** as part of the **Object Oriented Programming (OOP)** course project at the **Institute of Business Administration (IBA), Karachi**.

This project demonstrates the practical implementation of core OOP concepts such as:

* Encapsulation
* Inheritance
* Polymorphism
* Abstraction
* Dynamic Binding
* Composition
* Smart Pointers (`std::unique_ptr`)

The game supports:

* Human vs Human gameplay
* Human vs AI gameplay
* Move validation
* Check and Checkmate detection
* Stalemate detection
* Pawn Promotion
* Graphical User Interface using SFML

---

# 📌 Project Overview

This project is a fully interactive chess game built using modern C++ and SFML.

The objective of the project was to apply object-oriented programming concepts in a real-world software system.

The chessboard, pieces, movement system, and game logic were designed from scratch.

The project includes:

* Full chess board implementation
* Piece movement rules
* Turn management
* AI opponent with random legal moves
* Piece rendering using textures
* Game state management
* Menu system
* Safe move validation using check detection

---

# 🎯 Features

## ✅ Game Modes

### 1. Play vs AI

* User plays as White
* AI plays as Black
* AI generates random legal moves

### 2. Play with Friend

* Local multiplayer
* Alternating turns between White and Black

---

# ♜ Implemented Chess Mechanics

| Feature             | Status |
| ------------------- | ------ |
| Pawn Movement       | ✅ |
| Rook Movement       | ✅ |
| Bishop Movement     | ✅ |
| Knight Movement     | ✅ |
| Queen Movement      | ✅ |
| King Movement       | ✅ |
| Capturing           | ✅ |
| Check Detection     | ✅ |
| Checkmate Detection | ✅ |
| Stalemate Detection | ✅ |
| Pawn Promotion      | ✅ |
| Move Validation     | ✅ |
| AI Opponent         | ✅ |

---

# 🧠 OOP Concepts Used

## 1. Inheritance

All chess pieces inherit from the base `Piece` class.

```cpp
class Piece
{
protected:
    bool isWhite;
};
```

Derived classes:

* Pawn
* Rook
* Knight
* Bishop
* Queen
* King

---

## 2. Polymorphism

Each piece overrides:

```cpp
virtual std::vector<sf::Vector2i> getValidMoves(...)
```

This allows dynamic move generation based on piece type.

---

## 3. Encapsulation

Every class manages its own:

* Data
* Movement logic
* Rendering logic
* State management

---

## 4. Composition

The `Board` class contains:

```cpp
std::unique_ptr<Piece> grid[8][8];
```

This models a real chess board containing pieces.

---

## 5. Smart Pointers

The project uses:

```cpp
std::unique_ptr
```

Benefits:

* Automatic memory management
* Prevents memory leaks
* Safer ownership handling

---

# 🏗️ Project Structure

```text
Chess/
│
├── assets/
│   ├── Pawn.png
│   ├── Pawn_Black.png
│   ├── Rook.png
│   ├── Rook_Black.png
│   ├── Knight.png
│   ├── Knight_Black.png
│   ├── Bishop.png
│   ├── Bishop_Black.png
│   ├── Queen.png
│   ├── Queen_Black.png
│   ├── King.png
│   ├── King_Black.png
│   └── font.ttf
│
├── include/
│   ├── piece.h
│   ├── pawn.h
│   ├── rook.h
│   ├── knight.h
│   ├── bishop.h
│   ├── queen.h
│   ├── king.h
│   └── board.h
│
├── src/
│   ├── main.cpp
│   ├── board.cpp
│   ├── pawn.cpp
│   ├── rook.cpp
│   ├── knight.cpp
│   ├── bishop.cpp
│   ├── queen.cpp
│   └── king.cpp
│
├── CMakeLists.txt
├── CMakeSettings.json
└── README.md
```

---

# ⚙️ Technologies Used

| Technology | Purpose |
|---|---|
| C++17 | Core programming language |
| SFML 3.0 | Graphics and window management |
| CMake | Build system |
| Visual Studio | Development IDE |

---

# 🖥️ Setup Instructions

## Prerequisites

Before running the project, install:

* Visual Studio 2022
* CMake
* SFML 3.0+

---

# 📥 Installing SFML

## Step 1: Download SFML

Download SFML from:

https://www.sfml-dev.org/download.php

Choose:

* SFML 3.0+
* Visual Studio version compatible with your compiler

---

## Step 2: Extract SFML

Extract SFML to a directory such as:

```text
C:/SFML
```

---

## Step 3: Configure `CMakeSettings.json`

Update:

```json
"SFML_DIR": "C:/SFML"
```

with your actual SFML path.

---

# 🔨 Building from Source


## ⚡ Quick Build (Windows)

### Option 1: One-Click Build

```powershell
Double-click: Build.bat
```

### Option 2: Manual Build

```powershell
cd build
cmake ..
cmake --build .
```

---

# 📋 Requirements

| Tool | Download |
|------|----------|
| **CMake** (3.14+) | https://cmake.org/download/ |
| **MSYS2** (with g++) | https://www.msys2.org/ |
| **SFML 3.0** | Already included in project! |

---

## Installing MSYS2

1. Download MSYS2 from the link above
2. During installation, choose **UCRT64**
3. After installation, open the **MSYS2 UCRT64** terminal and run:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

---

# 🔨 Build Steps

## Step 1: Open Terminal

Open Command Prompt or PowerShell in the project folder.

---

## Step 2: Create Build Folder

```powershell
mkdir build
cd build
```

---

## Step 3: Configure Project

```powershell
cmake ..
```

---

## Step 4: Build Project

```powershell
cmake --build .
```

---

## Step 5: Run the Game

```powershell
./Chess.exe
```

---

# 🐛 Troubleshooting

## “SFML not found” Error

Make sure SFML is installed through MSYS2:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

---

## “CMAKE_CXX_COMPILER not found” Error

* Install MSYS2 correctly
* Use the **MSYS2 UCRT64** terminal
* Do NOT use Git Bash

---

## Build Fails?

Delete the build folder and rebuild:

```powershell
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

---

# 📦 What's Included

```text
Chess/
├── CMakeLists.txt      ← Build configuration
├── Build.bat           ← One-click build script
├── include/            ← Header files
├── src/                ← Source code
├── Assets/             ← Piece textures & assets
└── SFML-3.0.2/         ← Included SFML library
```

---

# 💡 Helpful Tips

* The first build may take longer
* Future builds will be significantly faster
* Use Visual Studio or VS Code for easier development

---

## Alternative: Visual Studio / VS Code Build

1. Open the project folder
2. Install the **CMake Tools** extension
3. Click **Configure**
4. Click **Build**
5. Run the executable

---

# 🎮 Controls

| Action | Mouse Input |
|---|---|
| Select Piece | Left Click |
| Move Piece | Right Click |
| Return to Menu | Click Menu Button |

---

# 🧩 Game Logic Explanation

## Piece Selection

The user selects a piece using left-click.

The game:

1. Detects the selected piece
2. Generates all possible moves
3. Filters illegal moves
4. Highlights valid moves

---

## Move Validation

Each piece generates mathematical moves.

The board then checks:

* Is the move inside the board?
* Is the target square occupied?
* Does the move expose the king to check?

Unsafe moves are removed.

---

## Check Detection

The system:

1. Finds the king position
2. Generates enemy moves
3. Checks if enemy attacks intersect the king

If true:

```text
King is in Check
```

---

## Checkmate Detection

A player is in checkmate when:

* Their king is in check
* No legal moves exist

---

## AI System

The AI:

1. Collects all legal moves
2. Stores them in a vector
3. Randomly selects one
4. Executes the move

The AI currently uses a random move strategy.

Future improvements may include:

* Minimax Algorithm
* Alpha-Beta Pruning
* Board Evaluation Functions

---

# 📚 Important Classes

## `Piece`

Base abstract class for all pieces.

Responsible for:

* Piece color
* Sprite handling
* Virtual movement functions

---

## `Board`

Manages:

* Chess grid
* Move validation
* Game rules
* Rendering
* Check detection
* AI movement

---

## `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, `King`

Derived classes implementing specific movement rules.

---

# 🖼️ GUI Features

* Interactive chess board
* Highlighted valid moves
* Piece textures
* Menu system
* Status messages
* Turn indicators

---

# 🚀 Future Improvements

Potential future features:

* Castling
* En Passant
* Better AI using Minimax
* Sound effects
* Online multiplayer
* Undo move system
* Move history
* Timers
* Saving/loading games
* Animation system

---

# 🐞 Known Limitations

* AI uses random move generation
* Castling not implemented
* En passant not implemented
* No move history tracking
* No networking support

---

# 📖 Learning Outcomes

This project helped in understanding:

* Real-world application of OOP
* Complex class relationships
* Game development architecture
* Event-driven programming
* GUI programming with SFML
* Memory management using smart pointers
* Chess rule implementation

---

# 👨‍💻 Authors

* Jiya Turshani
* Laksh Kumar
* Deepak Raj

BS Computer Science

Institute of Business Administration (IBA), Karachi

---

# 📜 License

This project was developed for educational purposes as part of an academic course project.

♟️ Happy Coding!