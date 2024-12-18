# The Table Engine

Welcome to The Table Engine, a custom-built game engine designed to streamline the creation of 2D games. This project was developed collaboratively by Arnav Narula, Kenny Li, Jeffrey Lin, and Buwei Chen.

## Features

- **GameObject Creation**: Design unique structures and entities with ease.
- **Bitmap Import and Animation**: Import bitmap files, animate them, and adjust settings with real-time previews.
- **Animation Segmentation**: Utilize bitmap segments for dynamic animations.
- **Property Editing**: Modify game object properties through intuitive popups, with auto-population based on selected types.
- **Custom Collision Logic**: Define and customize collision behaviors.
- **Configuration Integration**: Generate types and fields from configuration files.
- **Map and Level Design**: Create maps and levels with preview images and snap grids.
- **Seamless Mode Switching**: Effortlessly toggle between level editing and gameplay modes.

## Demo

Experience The Table Engine in action by visiting our [demo page](https://kli63.github.io/EngineDocs/).

## Screenshots

![Screenshot 1](https://kli63.github.io/EngineDocs/screenshot1.png)
![Screenshot 2](https://kli63.github.io/EngineDocs/screenshot2.png)
![Screenshot 3](https://kli63.github.io/EngineDocs/screenshot3.png)
![Screenshot 4](https://kli63.github.io/EngineDocs/screenshot4.png)

## Download and Compilation Instructions

To get started with The Table Engine:

1. **Download**: [TheTableEngine.zip](https://kli63.github.io/EngineDocs/TheTableEngine.zip)
2. **Extract**: Unzip the downloaded file.
3. **Navigate**: Open a terminal and navigate to the project's root directory.
4. **Compile**:
   - Change directory: `cd Engine`
   - Make the script executable: `chmod +x run.sh`
   - Run the script: `./run.sh`
5. **Launch**: Use the GUI to load the demo or start creating your own game.

## Documentation

Comprehensive documentation is available to guide you through The Table Engine's functionalities. Access it [here](https://kli63.github.io/EngineDocs/).

## Class Hierarchy

For an in-depth understanding of the engine's architecture, refer to the class hierarchy graph:

![Class Hierarchy Graph](https://kli63.github.io/EngineDocs/class_hierarchy.png)

## Post Mortem

Reflecting on our development journey, we found the project both challenging and rewarding. Initially, we focused on setting up pybind and developing a test dungeon crawler game, which provided a solid foundation in C++. Transitioning to the frontend, we utilized Python's tkinter library to create a tiling software equipped with a grid canvas and sprite map editor. Debugging the GUI presented challenges, particularly in managing data states and ensuring a seamless user experience. On the backend, we developed a pipeline to render game objects based on GUI data, encountering and overcoming obstacles related to data conversion and structure. With additional time, we would have enhanced the animation system, expanded weapon and enemy varieties, and incorporated more custom scripting support to increase the engine's versatility. Our collaborative efforts, brainstorming sessions, and problem-solving experiences made this project an invaluable learning opportunity.

For a detailed overview, visit our [post mortem page](https://kli63.github.io/EngineDocs/post_mortem.html).

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/kli63/EngineDocs/blob/main/LICENSE) file for details.

## Acknowledgments

We extend our gratitude to our mentors and peers who provided guidance and support throughout this project.

---

_Note: For the latest updates and contributions, visit our [GitHub repository](https://github.com/kli63/EngineDocs)._
::contentReference[oaicite:0]{index=0}
