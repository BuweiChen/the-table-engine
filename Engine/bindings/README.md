# Using Python Bindings for the CPSC411 Final Project Game Engine

This document provides detailed instructions on how to set up and use the Python bindings for the custom game engine developed in this project. The Python bindings allow you to interact with the game's internal systems (such as scenes, game objects, components, etc.) directly from Python scripts, facilitating rapid prototyping, scripting of game logic, and integration with various Python tools.

**Repository URL:**
https://github.com/Fall24BuildingGameEngines/finalproject-jeffreylinkennyliarnavnarulabuweichen.git

markdown
Copy code

## Motivation and Goals

The Python bindings are created using [pybind11](https://github.com/pybind/pybind11). The main goals of integrating Python into the engine are:

- **Scripting Flexibility:** Allow game designers and developers to write gameplay logic in Python, which is easier to iterate on compared to C++.
- **Rapid Prototyping:** Quickly experiment with gameplay elements, AI behaviors, and scene configuration without recompiling the entire engine.
- **Integration with Python Ecosystem:** Leverage Python libraries for debugging, testing, or content generation.

By exposing core engine classes (like `GameObject`, `Component`, `Script`, `SceneManager`, etc.) into Python, you can dynamically load scenes, manipulate objects, and run the game loop in a more interactive environment.

## Dependencies

Before attempting to use the Python bindings, ensure that the following dependencies are installed on your system:

### Common Dependencies (Linux & macOS)

- **CMake (>=3.10):** Used to configure and build the project.
- **Make:** On macOS, you may have `make` by installing Xcode Command Line Tools. On Linux, it usually comes pre-installed.
- **A C++ Compiler:** (e.g., `g++` on Linux, `clang++` on macOS) supporting C++17 or newer.
- **Python 3 (>=3.6):** Python 3 interpreter that will be used to run and load the bindings.
- **pybind11:** The project includes pybind11 as a submodule. You'll need to pull submodules after cloning the repo.
- **SDL2 & SDL2_image & SDL2_mixer:** The engine relies on SDL2 for windowing and input, and SDL2_image, SDL2_mixer for media.
- **PIL/Pillow (Python):** For image processing in Python (if the engine's GUI or scripts require it).
- **JSON for Modern C++:** Typically included as a submodule. Ensure it is pulled as well.

## Cloning the Repository

```bash
git clone https://github.com/Fall24BuildingGameEngines/finalproject-jeffreylinkennyliarnavnarulabuweichen.git
```

After cloning, navigate into the repository directory:

```bash
cd finalproject-jeffreylinkennyliarnavnarulabuweichen
```

### Pulling Submodules
The project may include submodules for pybind11 and other third-party libraries. Make sure to initialize and update them:

```bash
git submodule update --init --recursive
```

This ensures that pybind11 and any other external dependencies are properly fetched.

### Building the Engine and Python Bindings
There are scripts provided (compile.sh and compile_and_run.sh) that will help configure and build the project with Python bindings.

Linux and macOS
Ensure Python is in your PATH: Make sure python3 is available. The scripts will automatically detect your Python installation via which python3.

Run the compile script:

```bash
chmod +x compile.sh
./compile.sh
```
This script will:
- Remove any previous build directory.
- Create a new build directory.
- Run CMake, pointing it to your Python3 executable.
- Run make to build the engine and the Python module.
- After this step, you should have a build directory containing the compiled binaries and the engine Python module (as a .so file on Linux/macOS).

### Run the engine with Python support:

If you want to run the engine and test Python integration immediately, use compile_and_run.sh:

```bash
chmod +x compile_and_run.sh
./compile_and_run.sh
```

This script does the same as compile.sh but after building, it sets PYTHONPATH=build and then runs run.py using python3, which should load the engine module from the build directory.

### Running make all Manually
If you prefer a manual approach:

```bash
mkdir build
cd build
cmake -DPython3_EXECUTABLE=$(which python3) ..
make all
```

Make sure that you specify the Python executable if needed. make all will build the engine and the Python extension module.

### Using the Python Bindings
Once built, you will have a engine Python module in your build directory. You can start a Python interpreter in that directory or set PYTHONPATH to point to build.

For example:

```bash
export PYTHONPATH=build
python3
```

Now inside Python:

```python
import engine

# Create objects via the engine API
obj = engine.GameObject("Player")
print(obj.getTag())  # Interact with the game object

# Access SceneManager singleton
sm = engine.SceneManager.getInstance()
print(sm.getSceneIndex())

# Potentially start the game loop with Python controlling logic
app = engine.GameApplication("game")
app.start(demo=True)
app.runLoop()
```

You can script behaviors, create new GameObjects, attach Components or Scripts, and leverage the SceneManager to load or manipulate scenes.

### Notes and Tips
- Paths and Libraries: Ensure that any SDL2, SDL2_image, and SDL2_mixer dependencies are installed in system paths that CMake can find. On macOS, brew install sdl2 sdl2_image sdl2_mixer is often sufficient. On Linux, use your distribution's package manager (apt, dnf, yum, or pacman).

- Python Virtual Environments: If you use a virtual environment (venv), ensure you run compile.sh or compile_and_run.sh from within that environment so that the correct Python interpreter is detected.

- Debugging: If something fails, verify that:
    - python3 points to the correct interpreter.
    - make is installed and accessible. On macOS, install Xcode Command Line Tools if not already installed.
    - pybind11 and other submodules are properly checked out via git submodule update --init --recursive.
    - Dependencies such as SDL2 are installed.
Conclusion
By following these steps, you will have a compiled engine with Python bindings accessible from within Python. This integration significantly simplifies experimentation with new features, tweaking AI, or adding gameplay mechanics. The provided scripts and instructions should get you up and running quickly, both on Linux and macOS.