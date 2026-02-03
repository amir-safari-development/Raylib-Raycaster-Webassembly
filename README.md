<div align="center">

  <h1>🏰 RayCaster Engine</h1>
  
  <p>
    <b>A high-performance classic (Retro) 3D graphics engine, written in C language and Raylib library</b>
  </p>

  <p>
    <a href="https://github.com/amir-safari-development/Raylib-Raycaster/blob/main/LICENSE">
      <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">
    </a>
    <a href="https://en.wikipedia.org/wiki/C99">
      <img src="https://img.shields.io/badge/Language-C99-blue.svg" alt="Language">
    </a>
    <a href="https://www.raylib.com/">
      <img src="https://img.shields.io/badge/Powered%20by-Raylib-red.svg" alt="Raylib">
    </a>
  </p>

  <br>

  <a href="https://amir-safari-development.github.io/Raylib-Raycaster/">
    <img src="https://img.shields.io/badge/🌐_View_Project_Website-Live_Demo-2ea44f?style=for-the-badge" alt="Website Link">
  </a>

</div>

<br>

## 📖 About the Project

This project is a modern implementation of the Raycasting technique (the technique used in the game Wolfenstein 3D). Using the DDA algorithm and C language, this engine is capable of rendering 3D environments with high frame rates (60 FPS+) on Linux systems.

### ✨ Key Features

- 🚀 **Ultra-fast performance**: Written in pure C with optimized memory management.
- 📐 **DDA Algorithm**: Precise ray collision calculations for wall rendering.
- 🗺️ **Live Minimap**: Small 2D map for navigation in the environment.
- 👁️ **Dynamic FOV**: Ability to change field of view without image distortion (Fisheye Correction).
- 🐧 **Native Linux Support**: Easy compilation and execution with Make.

## Game Controls

- **W**: Go Forward
- **S**: Go Backward
- **D**: Go Right
- **A**: Go Left
- **Up Arrow**: Rotate to North
- **Down Arrow**: Rotate to South
- **Right Arrow**: Rotate to Right
- **Left Arrow**: Rotate to Left
- **M**: Toggle 2D/3D
- **Mouse Right Click**: Add Obstacle
- **Mouse Left Click**: Remove Obstacle

## 🛠️ How to Install and Run (Installation)

To run this project on Linux (Ubuntu/Debian), follow the steps below:

### 1. Prerequisites

Ensure that `gcc`, `make`, and the `raylib` library are installed:

```bash
sudo apt update
sudo apt install build-essential git
# Install Raylib (refer to Raylib documentation if needed)
```
