/**
 * @file python_guide.h
 * @brief Technical guide and documentation for the Game Engine Python Bindings
 *
 * @page Game Engine Python Bindings
 *
 * @section intro_sec Introduction
 *
 * The Game Engine Python Bindings provide a bridge between high-level Python game development 
 * and our performant C++ engine core. This integration combines Python's ease of use with C++'s
 * performance capabilities.
 *
 * Key advantages:
 * - Rapid Development using Python's intuitive syntax
 * - Performance from C++ engine core
 * - Flexibility to mix Python scripting with C++ components
 * - Accessible game development for Python developers
 *
 * @section setup_sec Setup and Installation
 *
 * @subsection prereq_subsec Prerequisites
 * - Python 3.10+
 * - CMake 3.15+
 * - C++17 compatible compiler
 * - SDL2 development libraries
 * - pybind11 (included as submodule)
 *
 * @subsection install_ubuntu Ubuntu/Debian Installation
 * @code{.sh}
 * # Install Python and development tools
 * sudo apt-get update
 * sudo apt-get install python3 python3-dev python3-pip
 *
 * # Install CMake
 * sudo apt-get install cmake
 *
 * # Install SDL2 dependencies
 * sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
 *
 * # Optional: Documentation tools
 * sudo apt-get install doxygen graphviz
 * @endcode
 *
 * @subsection install_mac macOS Installation
 * @code{.sh}
 * # Using Homebrew
 * brew install python cmake sdl2 sdl2_ttf sdl2_image sdl2_mixer
 * brew install doxygen graphviz  # Optional for docs
 * @endcode
 *
 * @section arch_sec Architecture
 *
 * @subsection arch_layers Layer Structure
 *
 * The bindings are organized in three main layers:
 * 1. C++ Engine Core
 *    - Performance-critical systems
 *    - Core game object architecture
 *    - SDL2 integration
 *
 * 2. pybind11 Binding Layer
 *    - Type conversion
 *    - Exception handling
 *    - Method exposure
 *
 * 3. Python Interface
 *    - High-level game logic
 *    - Scene management
 *    - Event handling
 *
 * @section usage_sec Usage Examples
 *
 * @subsection basic_example Basic Game Setup
 * @code{.py}
 * import engine
 *
 * def main():
 *     # Initialize game
 *     app = engine.GameApplication("My Game")
 *     app.start(False)  # Normal mode
 *     
 *     # Create player
 *     player = engine.GameObjectFactory.createPlayerTest()
 *     
 *     # Game loop
 *     while app.m_gameIsRunning:
 *         app.input()
 *         app.update()
 *         app.render()
 *         app.advanceFrame()
 *
 * if __name__ == "__main__":
 *     main()
 * @endcode
 *
 * @subsection custom_component Custom Component Example
 * @code{.py}
 * import engine
 *
 * class CustomBehavior(engine.Script):
 *     def __init__(self):
 *         super().__init__("CustomBehavior")
 *         self.timer = 0
 *     
 *     def update(self):
 *         self.timer += 1
 *         if self.timer > 60:  # Every second at 60 FPS
 *             print("Tick!")
 *             self.timer = 0
 * @endcode
 *
 * @subsection scene_example Scene Management
 * @code{.py}
 * import engine
 *
 * def create_level():
 *     manager = engine.SceneManager.getInstance()
 *     
 *     # Create background
 *     for x in range(10):
 *         for y in range(10):
 *             tile = engine.GameObjectFactory.createTile1()
 *             transform = tile.getComponent(engine.Transform)
 *             transform.setWorldPosition(x * 32, y * 32)
 * @endcode
 *
 * @section perform_sec Performance Considerations
 *
 * @subsection perf_obj Object Lifetime
 * - Use appropriate pybind11 return value policies
 * - Avoid circular references
 * - Properly manage SDL resources
 *
 * @subsection perf_data Data Transfer
 * - Minimize language boundary crossings
 * - Batch operations when possible
 * - Choose appropriate data structures
 *
 * @subsection perf_thread Threading
 * - Be aware of Python's GIL
 * - Ensure thread safety in C++ components
 * - Handle async operations appropriately
 *
 * @section extend_sec Extension Guide
 *
 * @subsection extend_comp Adding Components
 * 1. Create C++ component class
 * 2. Add pybind11 bindings in engine_bindings.cpp
 * 3. Document Python interface
 *
 * Example component binding:
 * @code{.cpp}
 * py::class_<NewComponent, Component>(m, "NewComponent")
 *     .def(py::init<>())
 *     .def("newMethod", &NewComponent::newMethod)
 *     .def("update", &NewComponent::update);
 * @endcode
 *
 * @subsection extend_resource Custom Resources
 * 1. Implement C++ resource class
 * 2. Add memory management
 * 3. Create Python interface
 * 4. Document usage
 *
 * @section best_sec Best Practices
 *
 * @subsection best_code Code Organization
 * - Keep Python code high-level and focused on game logic
 * - Move performance-critical code to C++
 * - Use appropriate abstraction levels
 *
 * @subsection best_error Error Handling
 * - Translate exceptions between languages
 * - Provide clear error messages
 * - Handle failures gracefully
 *
 * @subsection best_doc Documentation
 * - Maintain clear API documentation
 * - Provide example code
 * - Note performance implications
 *
 * @section future_sec Future Development
 *
 * @subsection future_features Planned Features
 * - Enhanced component system
 * - Extended scripting capabilities
 * - Additional factory methods
 * - Physics system integration
 * - Networking support
 *
 * @subsection future_opt Optimization Plans
 * - Memory pooling
 * - Batched rendering
 * - Component update optimization
 *
 * @section contrib_sec Contributing
 *
 * @subsection contrib_guide Contribution Guidelines
 * 1. Follow existing patterns
 * 2. Maintain documentation
 * 3. Include tests
 * 4. Consider performance
 *
 * @section ref_sec References
 *
 * @subsection ref_docs Documentation
 * - [pybind11 Documentation](https://pybind11.readthedocs.io/)
 * - [SDL2 Wiki](https://wiki.libsdl.org/)
 *
 * @subsection ref_design Design Patterns
 * - Type conversion guidelines
 * - Memory management strategies
 * - Performance optimization techniques
 */