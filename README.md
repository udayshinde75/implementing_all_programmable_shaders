# Implementing All Programmable Shaders

A small OpenGL project demonstrating the programmable shader pipeline: vertex, fragment, geometry, and tessellation shaders.

**Features:**
- Loads and compiles shader stages from `assets/shaders/`.
- Example shader files for vertex, fragment, geometry, tessellation control and evaluation.
- Uses GLFW and GLAD for window/context and function loading.

**Prerequisites**
- CMake (>= 3.10)
- A C++17 toolchain (clang/g++)
- OpenGL drivers, GLFW, GLM, Assimp available on your system

**Build**
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

The project builds an executable named `OpenGLShader`.

**Run**
From the `build/` directory run:
```bash
./OpenGLShader
```

**Repository layout**
- `assets/shaders/` — GLSL shader sources
- `include/graphics/Shader.hpp` — Shader helper header
- `src/graphics/Shader.cpp` — Shader helper implementation
- `src/main.cpp` — Application entry
- `external/` — vendored dependencies (GLAD, GLFW headers)

**Notes**
- Update or replace shaders in `assets/shaders/` to experiment.