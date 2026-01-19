# Pac-Man

This project is my implementation of the arcade classic Pac-Man, developed in C++ using the SFML (Simple and Fast Multimedia Library). The goal was to program the fundamental mechanics of a maze game and the enemy AI logic from scratch.

> Read this in [German](README.de.md).

🕹️ **The Game**

### Gameplay

The player controls Pac-Man through a maze with the objective of eating all the pellets while evading four ghosts. Key features include:

- **AI Behavior:** Each ghost (Blinky, Pinky, Inky, and Clyde) features its own unique pursuit pattern.
- **Power Pellets:** Collecting large pellets makes the ghosts temporarily vulnerable, allowing Pac-Man to eat them.
- **Level Structure:** A classic tile-based maze featuring teleportation tunnels on the sides.

### Controls

* **Move Pac-Man:** `W` (Up), `A` (Left), `S` (Down), `D` (Right) or the Arrow Keys.

---

## 🚀 Download & Website

Want to try the game directly without compiling it yourself? You can find the executable file (.exe / App) and further information on my website:

🔗 Click here for the [Website](https://jjmercado.github.io/portfolioSite/games/pac-man) and Download

---

## 🛠️ Build Instructions (Local Build)

This project uses CMake to manage the build process across different platforms.

### Prerequisites

- A **C++17** capable compiler (GCC, Clang, or MSVC).
- **CMake** (Version 3.10 or higher).
- **SFML 2.6.2** (An update to the latest SFML version will follow when time permits).

### Step-by-Step

1. **Clone the Repository:**
```bash
git clone https://github.com/jjmercado/Pac-Man
cd pac-man

```


2. **Create a Build Directory:**
```bash
mkdir build
cd build

```


3. **Configure CMake:**
```bash
cmake ..

```


4. **Build the Project:**
```bash
cmake --build .

```


5. **Run the Game:**
After the build is complete, you will find the executable file in the `build` folder (or under `build/Debug` / `build/Release` on Windows).

---

## 📜 License & Copyright

The code for this project is licensed under the **MIT License**.

- **Code:** The source code is open for study and use in your own projects under the MIT License.
- **Assets & Content:** All images, videos, and text are my intellectual property (Copyright) and are not covered by the MIT License. Commercial use of these assets is prohibited without express permission.