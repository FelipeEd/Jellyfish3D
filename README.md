# Jellyfish3D

A 3D Graphics Engine originally developed as a distinguished academic project at UFMG. This engine showcases advanced 3D rendering techniques including physically-based rendering (PBR), complex model loading, lighting, skyboxes, and interactive simulations.

## Build & Run

**Linux (with helper scripts):**
```bash
./build.sh          # Build (debug)
./run.sh            # Interactive menu to run examples
```

**Manual (Linux/Windows/Mac):**
```bash
cmake --preset debug
cmake --build build/debug

# Run
./build/debug/bin/Sandbox    # Linux/Mac
build\debug\bin\Sandbox.exe  # Windows
```

## System Dependencies

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake libx11 libxrandr libxinerama libxcursor libxi
```

**Ubuntu/Debian:**
```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**Windows:** Visual Studio with CMake support or MinGW

**Libraries:** GLFW, GLM, GLAD, ImGui, STB (automatically downloaded by CMake)

## Imagens

![Alt text](Prints/Sandbox.png?raw=true "Sandbox")
![Alt text](Prints/Boids.png?raw=true "Boids")
