# 🌟 Labyrinth - Interactive Maze Game

A sophisticated maze generation and solving game implemented in C with SDL graphics support. This project demonstrates advanced algorithms for maze generation using Randomized Depth-First Search and provides an interactive gaming experience with multiple difficulty levels.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C-blue.svg)
![Graphics](https://img.shields.io/badge/graphics-SDL%201.2-green.svg)

## 📋 Table of Contents

- [Features](#-features)
- [Screenshots](#-screenshots)
- [Algorithm Overview](#-algorithm-overview)
- [Prerequisites](#-prerequisites)
- [Installation](#-installation)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Technical Details](#-technical-details)
- [Controls](#-controls)
- [Building from Source](#-building-from-source)
- [Contributing](#-contributing)
- [License](#-license)

## ✨ Features

### 🎮 Game Features
- **Interactive Graphics**: Beautiful SDL-based graphical interface
- **Multiple Difficulty Levels**: Easy, Medium, and Hard maze configurations
- **Real-time Maze Generation**: Watch mazes being generated using advanced algorithms
- **Intelligent Maze Solving**: Automatic pathfinding with visual solution display
- **Responsive Controls**: Smooth keyboard navigation and menu interaction
- **Visual Feedback**: Interactive ball movement and trophy collection

### 🔧 Technical Features
- **Randomized DFS Algorithm**: Advanced maze generation using depth-first search
- **Memory Efficient**: Optimized data structures and memory management
- **Modular Design**: Clean separation of concerns with well-organized modules
- **Cross-platform Compatible**: Runs on Linux, macOS, and Windows
- **Professional Documentation**: Comprehensive code documentation with Doxygen-style comments

## 🖼️ Screenshots

<p align="center">
    <img src="https://i.imgur.com/Tc1KGP1.png" alt="screenshot">
</p>

## 🧠 Algorithm Overview

### Maze Generation - Randomized Depth-First Search
1. **Initialization**: Start with a grid of cells, all walls intact
2. **Random Selection**: Choose a random starting cell and mark it as visited
3. **Neighbor Analysis**: Find all unvisited neighboring cells
4. **Random Movement**: Randomly select an unvisited neighbor
5. **Wall Removal**: Remove the wall between current cell and chosen neighbor
6. **Stack Management**: Push current cell to stack and move to neighbor
7. **Backtracking**: When no unvisited neighbors exist, pop from stack
8. **Completion**: Continue until all cells have been visited

### Maze Solving - Depth-First Search with Backtracking
1. **Path Tracking**: Use a stack to maintain the current path
2. **Direction Selection**: Randomly choose valid directions (open passages)
3. **Dead End Handling**: Backtrack when reaching dead ends
4. **Solution Path**: Return the complete path from entry to exit

## 🛠️ Prerequisites

### System Requirements
- **Operating System**: Linux (Ubuntu/Debian recommended), macOS, or Windows with WSL
- **Compiler**: GCC with C99 support or later
- **Memory**: Minimum 64MB RAM
- **Display**: Support for graphical display (for SDL interface)

### Required Libraries
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential libsdl1.2-dev libsdl-image1.2-dev pkg-config

# macOS (with Homebrew)
brew install sdl sdl_image pkg-config

# Fedora/CentOS/RHEL
sudo yum install gcc make SDL-devel SDL_image-devel pkgconfig
```

## 🚀 Installation

### Quick Start (Recommended)
```bash
# Clone the repository
git clone https://github.com/HamzaBenyazid/labyrinth.git
cd labyrinth

# Build the project
make

# Run the game
./bin/labyrinth
```

### Manual Installation
1. **Download**: Clone or download the project files
2. **Dependencies**: Install SDL development libraries (see Prerequisites)
3. **Compile**: Use the provided Makefile or compile manually
4. **Execute**: Run the generated executable

## 🎯 Usage

### Starting the Game
```bash
./bin/labyrinth
```

### Game Flow
1. **Main Menu**: Choose to start a new game or view controls
2. **Difficulty Selection**: Select Easy (10x10), Medium (15x15), or Hard (20x20)
3. **Maze Generation**: Watch the maze being generated in real-time
4. **Navigation**: Use arrow keys to move through the maze
5. **Objective**: Reach the trophy (exit point) to complete the level
6. **Solution**: Press 'S' to reveal the solution path

## 📁 Project Structure

```
labyrinth/
├── 📁 src/                     # Source code files
│   ├── 📄 main.c              # Application entry point
│   ├── 📄 maze_generator.c    # Maze generation algorithms
│   ├── 📄 maze_solver.c       # Maze solving algorithms
│   ├── 📄 stack.c             # Stack data structure implementation
│   ├── 📄 display.c           # Console display functions
│   └── 📄 sdl_display.c       # SDL graphics interface
├── 📁 include/                 # Header files
│   ├── 📄 maze_generator.h    # Maze generation declarations
│   ├── 📄 maze_solver.h       # Maze solving declarations
│   ├── 📄 stack.h             # Stack data structure declarations
│   ├── 📄 display.h           # Display function declarations
│   └── 📄 sdl_display.h       # SDL interface declarations
├── 📁 images/                  # Game assets and graphics
│   ├── 🖼️ background.png      # Game background
│   ├── 🖼️ controls.png        # Control instructions
│   ├── 🖼️ difficulty icons   # Difficulty level icons
│   └── 🖼️ game sprites       # Ball, trophy, and other sprites
├── 📁 bin/                     # Compiled binaries (generated)
├── 📄 Makefile                # Build configuration
└── 📄 README.md               # Project documentation
```

## 🔧 Technical Details

### Data Structures

#### Cell Structure
```c
typedef struct _cell {
    int right;  // Right wall status (0/1/-1)
    int left;   // Left wall status  
    int up;     // Top wall status
    int down;   // Bottom wall status
} cell;
```

#### Stack Implementation
```c
typedef struct _stack {
    int column;           // Column coordinate
    int row;             // Row coordinate  
    struct _stack *next; // Next node pointer
} stack;
```

### Key Algorithms

#### Maze Generation Time Complexity
- **Time**: O(n) where n is the number of cells
- **Space**: O(n) for the visited array and stack

#### Maze Solving Time Complexity  
- **Worst Case**: O(4^n) for backtracking
- **Average Case**: O(n) for most mazes
- **Space**: O(n) for the solution path stack

### Memory Management
- Dynamic allocation for maze matrices
- Proper cleanup of stack structures
- SDL surface management for graphics
- No memory leaks in normal operation

## 🎮 Controls

### Menu Navigation
- **Arrow Keys**: Navigate menu options
- **Enter/Space**: Select menu item
- **Escape**: Return to previous menu or quit

### Gameplay Controls
- **↑ Arrow**: Move up
- **↓ Arrow**: Move down  
- **← Arrow**: Move left
- **→ Arrow**: Move right
- **S Key**: Show/hide solution path
- **R Key**: Restart current maze
- **Escape**: Return to main menu

### Difficulty Levels
- **Easy**: 10×10 maze - Perfect for beginners
- **Medium**: 15×15 maze - Moderate challenge
- **Hard**: 20×20 maze - For experienced players

## 🔨 Building from Source

### Using Makefile (Recommended)
```bash
# Clean previous builds
make clean

# Build the project
make

# Run with debug information
make debug

# Install system-wide (optional)
make install
```

### Manual Compilation
```bash
# Create build directory
mkdir -p bin

# Compile source files
gcc -Wall -Wextra -pedantic -g `pkg-config --cflags sdl` -Iinclude -c src/*.c

# Link the executable
gcc *.o -o bin/labyrinth `pkg-config --libs sdl` `pkg-config --libs SDL_image`

# Clean object files
rm *.o
```

### Debug Build
```bash
# Build with debug symbols and additional warnings
make DEBUG=1

# Run with memory checking (if valgrind is installed)
valgrind --leak-check=full ./bin/labyrinth
```

## 🤝 Contributing

We welcome contributions to improve the Labyrinth project! Here's how you can help:

### Ways to Contribute
- 🐛 **Bug Reports**: Report issues or unexpected behavior
- 💡 **Feature Requests**: Suggest new features or improvements
- 🔧 **Code Contributions**: Submit pull requests with enhancements
- 📖 **Documentation**: Improve or expand documentation
- 🎨 **Assets**: Contribute graphics, sounds, or visual improvements

### Development Setup
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit your changes (`git commit -m 'Add amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

### Coding Standards
- Follow existing code style and formatting
- Add appropriate documentation for new functions
- Include unit tests for new functionality
- Ensure memory management is proper
- Test on multiple platforms when possible

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 HamzaBenyazid and Mohammed Bekraoui

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## 🙏 Acknowledgments

- **SDL Development Team**: For the excellent SDL library
- **Algorithm Inspiration**: Classic maze generation algorithms from computer science literature
- **Community**: Thanks to all contributors and users who help improve this project

## 📞 Support & Contact

- **GitHub Issues**: [Report bugs or request features](https://github.com/HamzaBenyazid/labyrinth/issues)
- **Email**: [contact@example.com](mailto:contact@example.com)
- **Documentation**: Additional documentation available in the `docs/` directory

---

**Made with ❤️ by @HamzaBenyazid and @meedbek**

*Happy maze solving! 🎮✨*


