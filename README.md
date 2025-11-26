# Jellyfish3D

Engine gráfica 3D desenvolvida para a disciplina de Computação Gráfica na UFMG. Implementa renderização PBR, carregamento de modelos 3D, sistema de iluminação e skybox.

## Build & Run

**Linux (com scripts auxiliares):**
```bash
./build.sh          # Compila (debug)
./run.sh            # Menu interativo para executar exemplos
```

**Manual (Linux/Windows/Mac):**
```bash
cmake --preset debug
cmake --build build/debug

# Executar
./build/debug/bin/Sandbox    # Linux/Mac
build\debug\bin\Sandbox.exe  # Windows
```

## Dependências do Sistema

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake libx11 libxrandr libxinerama libxcursor libxi
```

**Ubuntu/Debian:**
```bash
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**Windows:** Visual Studio com CMake support ou MinGW

**Bibliotecas:** GLFW, GLM, GLAD, ImGui, STB (baixadas automaticamente pelo CMake)

## Imagens

![Alt text](Prints/Sandbox.png?raw=true "Sandbox")
![Alt text](Prints/Boids.png?raw=true "Boids")
