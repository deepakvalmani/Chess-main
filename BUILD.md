# Building Chess from Source

## ⚡ Quick Build (Windows)

### Option 1: One-Click Build
```
Double-click: Build.bat
```

### Option 2: Manual Build
```powershell
cd build
cmake ..
cmake --build .
```

---

## 📋 Requirements

| Tool | Download |
|------|----------|
| **CMake** (3.14+) | https://cmake.org/download/ |
| **MSYS2** (with g++) | https://www.msys2.org/ |
| **SFML 3.0** | Already included in project! |

### Installing MSYS2
1. Download MSYS2 from the link above
2. During install, choose "UCRT64"
3. After install, run this in MSYS2 UCRT64 terminal:
```
pacman -S mingw-w64-ucrt-x86_64-sfml
```

---

## 🔨 Build Steps

### Step 1: Open Terminal
Open Command Prompt or PowerShell in this folder.

### Step 2: Create Build Folder
```powershell
mkdir build
cd build
```

### Step 3: Configure
```powershell
cmake ..
```

### Step 4: Build
```powershell
cmake --build .
```

### Step 5: Run
```powershell
./Chess.exe
```

---

## 🐛 Troubleshooting

### "SFML not found" error?
→ Make sure MSYS2 is installed with SFML:
```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

### "CMAKE_CXX_COMPILER not found"?
→ Install MSYS2 and open "MSYS2 UCRT64" terminal (not Git Bash)

### Build fails?
→ Delete the `build` folder and try again:
```powershell
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

---

## 📦 What's Included

```
Chess/
├── CMakeLists.txt      ← Don't touch this
├── Build.bat           ← One-click build (Windows)
├── BUILD.md           ← This file
├── include/            ← Header files
├── src/                ← Source code
├── Assets/             ← Images & sounds
└── SFML-3.0.2/         ← SFML library (included!)
```

---

## 💡 Tips

- **First build** takes longer. Subsequent builds are fast!
- **Use Visual Studio** instead of CMake? See alternate instructions below.

### Alternative: Visual Studio Build
1. Open the folder in VS Code
2. Install "CMake Tools" extension
3. Click "Configure" at the bottom
4. Click "Build"

---

## ❓ Need Help?

If build fails:
1. Check CMake version: `cmake --version`
2. Check g++ version: `g++ --version`
3. Verify all files are present in the folder

---
*Happy coding! ♟️*