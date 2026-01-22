# 🚀 Space Invaders – C/SDL2 Game

A school project featuring a classic **2D arcade shooter inspired by the legendary Space Invaders**, developed in **C** using the **SDL2** library.  
The player controls a spaceship and attempts to fend off an invasion of enemy ships.

## 🎮 Features

- Main menu
- High score leaderboard
- Simple in-game tutorial/instructions

## 🕹 Controls

| Key | Action |
|--------|--------|
| ⬆ / ⬇ | Menu navigation |
| ENTER | Confirm selection |
| ⬅ / ➡ | Move ship |
| SPACE | Fire projectile |
| ESC | Return to menu |

Additional instructions may be displayed directly on the screen during gameplay.

## 🎯 Objective

- Destroy all enemy ships
- Achieve the highest possible score

The game ends if:
- The player loses all lives  
- Enemy ships reach the bottom of the screen  

## 👩🏻‍💻 Technologies Used

- **Language:** C
- **Graphics Library:** SDL2
- **Build System:** CMake

## 📸 Screenshots
<img width="750" alt="image" src="https://github.com/user-attachments/assets/6661e0e2-4db3-4b18-bef5-8470fd31221a" />
<img width="750" alt="image" src="https://github.com/user-attachments/assets/791ea864-ee3d-4a63-bb0c-53a269589696" />
<img width="750" alt="image" src="https://github.com/user-attachments/assets/f9d602de-e4de-43df-9143-cb0aee6cf542" />

## ⚙️ Installation and Execution 

This project requires a Linux environment and installed SDL2 libraries.

### 1️⃣ Cloning the Project
```bash
git clone https://github.com/LenkaCiahotna/spaceInvadors-VSB.git
```

### 2️⃣Installing Dependencies

To successfully compile and run the game, the following libraries must be installed:

- GCC (or another C compiler)
- CMake
- SDL2
- SDL2_image
- SDL2_ttf

Installation: 
```bash
sudo apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
 ```

### 3️⃣ Running the Game

After downloading the files, you must first compile the program. This is done by entering the following commands in sequence:

- mkdir -p 
- build cd 
- build cmake .. 
- make 

If everything proceeds without issues, you can run the program. The executable file is located in the build folder.

Run the program using:
```bash
./spaceinvaders
```
