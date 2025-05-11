# Asteroid-Destroyer-Shahzad-Hussain

Asteroid Destroyer is a fast-paced, 2D arcade shooter developed in **C++ using the SFML (Simple and Fast Multimedia Library)**. Take control of a space ship, shoot down incoming asteroids, and survive for as long as possible!

![image](https://github.com/user-attachments/assets/e159c6a0-b868-4b30-958e-a3a6e6a8290f)

## 🎮 Game Features

- 👾 Simple, addictive gameplay loop
- 💥 Bullet-asteroid collision detection
- 🪨 Randomized asteroid spawning
- 🧠 Object-oriented C++ design
- 🎨 SFML-based graphics and rendering

## 📂 Project Structure

Asteroid-Destroyer/
- ├── Asteroid.h / Asteroid.cpp # Asteroid class: movement, rendering, off-screen check
- ├── Bullet.h / Bullet.cpp # Bullet class: firing, movement, off-screen logic
- ├── Game.h / Game.cpp # Main game engine: game loop, input, updates, rendering
- ├── main.cpp # Program entry point
- ├── player.png # Player ship texture
- ├── asteroid.png # Asteroid texture
- ├── bullet.png # Bullet texture

## 🛠️ Getting Started

### ✅ Prerequisites

- A C++17 compatible compiler
- SFML 2.5+ installed on your system

### ⚙️ Compilation Instructions

Using **g++** (Linux/macOS):

```bash
g++ main.cpp Game.cpp Asteroid.cpp Bullet.cpp -o AsteroidDestroyer -lsfml-graphics -lsfml-window -lsfml-system
./AsteroidDestroyer
```

🕹️ Controls

| Key                          | Action          |
| ---------- | --------------- |
| `⬅️` / `➡️` &  `⬆️` / `⬇️` | Move left/right & Rotate left or Right|
| `Spacebar/Mouse left Button` | Fire bullet     |
| `Esc`                        | Close window    |
| `Press 1`                    | Start Game      |
| `Press 2`                    | See High Score  |
| `Press 3`                    | Exit Game       |

🧠 Code Highlights

- Uses OOP design patterns with classes for Bullet, Asteroid, and Game.
- Efficient memory handling with std::vector and erase-remove idiom.
- Time-based movement using sf::Clock and sf::Time.

💡 Future Improvements

- Add scoring and lives
- Implement sound effects and music
- Introduce power-ups and multiple asteroid types
- Main menu and game over screen

📸 Screenshots

![image](https://github.com/user-attachments/assets/a041cf88-9d6c-480a-94c7-aa6067ee8fd5)

![image](https://github.com/user-attachments/assets/c6623b30-43b5-46f2-99af-0c1f81871e7f)

![image](https://github.com/user-attachments/assets/b26dd946-5c18-4200-bb2f-a0b5503c5fc3)


👨‍💻 Author
Shahzad Hussain
📫 [Contact Me] (shazadhussain74303@gmail.com)

