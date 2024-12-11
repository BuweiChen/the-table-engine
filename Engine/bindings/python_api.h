/** @page python_bindings Python API Reference
 * @brief Complete documentation for the Game Engine Python API
 * 
 * @tableofcontents
 * 
 * @section overview Overview
 * This page provides comprehensive documentation for all classes and methods available in the Python API.
 * 
 * @section core_classes Core Classes
 * 
 * @subsection vec2_class Vec2
 * 2D Vector class for positions and sizes.
 * ```python
 * # Create a vector
 * position = engine.Vec2(100.0, 200.0)
 * print(f"Position: ({position.x}, {position.y})")
 * ```
 * 
 * Methods:
 * - `Vec2()` - Create a zero vector
 * - `Vec2(x: float, y: float)` - Create a vector with coordinates
 * - `x: float` - X coordinate
 * - `y: float` - Y coordinate
 * 
 * @subsection gameobject_class GameObject
 * Base class for all game entities.
 * ```python
 * # Create a game object
 * player = engine.GameObject("player")
 * 
 * # Add components
 * transform = engine.Transform(100, 100)
 * player.addComponent(transform)
 * 
 * # Get component
 * player_transform = player.getComponent(engine.Transform)
 * ```
 * 
 * Methods:
 * - `GameObject(tag: str)` - Create a game object with tag
 * - `getId() -> str` - Get unique identifier
 * - `getTag() -> str` - Get object tag
 * - `addComponent(component: Component)` - Add a component
 * - `getComponent(type) -> Component` - Get component by type
 * - `addScript(script: Script)` - Add a script
 * - `getScript(type) -> Script` - Get script by type
 * - `input()` - Process input
 * - `update()` - Update object state
 * - `render()` - Render object
 * 
 * @subsection component_class Component
 * Base class for all components.
 * ```python
 * # Create and use a component
 * component = engine.Component("my_component")
 * component.setName("new_name")
 * owner = component.getOwner()
 * ```
 * 
 * Methods:
 * - `Component()` - Default constructor
 * - `Component(name: str)` - Create with name
 * - `getName() -> str` - Get component name
 * - `getOwner() -> GameObject` - Get owning object
 * - `setName(name: str)` - Set component name
 * - `setOwner(owner: GameObject)` - Set owner
 * 
 * @section components Component Types
 * 
 * @subsection transform_component Transform
 * Handles position and size in world space.
 * ```python
 * transform = engine.Transform(100, 100)
 * transform.setWorldPosition(50.0, 50.0)
 * transform.setWorldSize(32.0, 32.0)
 * ```
 * 
 * Methods:
 * - `Transform()` - Default constructor
 * - `Transform(x: int, y: int)` - Create at position
 * - `setWorldPosition(x: float, y: float)` - Set position
 * - `setWorldSize(width: float, height: float)` - Set size
 * - `getWorldPosition() -> Vec2` - Get position
 * - `getScreenPosition() -> Vec2` - Get screen position
 * 
 * @subsection collide_component Collide
 * Handles collision detection.
 * ```python
 * collider = engine.Collide()
 * collider.setScreenSize(32, 32)
 * collider.setScreenPosition(100, 100)
 * ```
 * 
 * Methods:
 * - `Collide()` - Default constructor
 * - `setScreenSize(width: int, height: int)` - Set collision box size
 * - `setScreenPosition(x: int, y: int)` - Set collision box position
 * - `isColliding(other: Collide) -> bool` - Check collision
 * 
 * * @subsection texture_component Texture
 * Base class for rendering textures and sprites.
 * ```python
 * texture = engine.Texture()
 * texture.setSizeInSpriteMap(32, 32)
 * texture.setPositionInSpriteMap(0, 0)
 * texture.setFlipHorizontal(False)
 * ```
 * 
 * Methods:
 * - `Texture()` - Default constructor
 * - `setSizeInSpriteMap(w: int, h: int)` - Set sprite size
 * - `setPositionInSpriteMap(x: int, y: int)` - Set sprite position
 * - `setFlipHorizontal(flip: bool)` - Set horizontal flip
 * - `setFlipVertical(flip: bool)` - Set vertical flip
 * - `setAngle(angle: float)` - Set rotation angle
 * 
 * @subsection animation_component Animation
 * Handles sprite sheet animations, inherits from Texture.
 * ```python
 * # Create animated sprite
 * animation = engine.Animation()
 * animation.setRowsColsInSpriteMap(1, 6)  # 1 row, 6 frames
 * animation.setAnimationTime(0.5)         # Half second per cycle
 * animation.play()                        # Start animation
 * 
 * # Control animation
 * animation.pause()                       # Pause at current frame
 * animation.setFrame(2)                   # Jump to specific frame
 * print(f"Current frame: {animation.getCurrentFrame()}")
 * ```
 * 
 * Methods:
 * - `Animation()` - Default constructor
 * - `getRows() -> int` - Get number of rows
 * - `getCols() -> int` - Get number of columns
 * - `getNumFrames() -> int` - Get total frames
 * - `setAutoPlay(autoplay: bool)` - Set auto-play state
 * - `setRowsColsInSpriteMap(rows: int, cols: int)` - Set sprite sheet layout
 * - `setAnimationTime(time: float)` - Set animation cycle time
 * - `play()` - Start/resume animation
 * - `pause()` - Pause animation
 * - `setFrame(frame: int)` - Set specific frame
 * - `getCurrentFrame() -> int` - Get current frame
 * - `isPlaying() -> bool` - Check if playing
 * 
 * @section factory Factory Methods
 * 
 * @subsection gameobject_factory GameObjectFactory
 * Creates predefined game objects.
 * ```python
 * # Create game objects
 * player = engine.GameObjectFactory.createPlayerTest()
 * enemy = engine.GameObjectFactory.createEnemyWarrior()
 * arrow = engine.GameObjectFactory.createArrow()
 * ```
 * 
 * Static Methods:
 * - `createPlayerTest() -> GameObject` - Create player
 * - `createBow() -> GameObject` - Create bow
 * - `createArrow() -> GameObject` - Create arrow
 * - `createEnemyWarrior() -> GameObject` - Create enemy
 * - `createTile1() -> GameObject` - Create tile
 * - `createKey() -> GameObject` - Create key
 * 
 * @section scripts Script Types
 * 
 * @subsection player_input_script PlayerInputScript
 * Handles player behavior.
 * ```python
 * player = engine.GameObject("player")
 * script = engine.PlayerInputScript()
 * player.addScript(script)
 * ```
 * 
 * Methods:
 * - `PlayerInputScript()` - Create script
 * - `getKeysCollected() -> int` - Get collected keys
 * - `update()` - Update player
 * 
 * @section managers Managers
 * 
 * @subsection scene_manager SceneManager
 * Manages game scenes and objects.
 * ```python
 * manager = engine.SceneManager.getInstance()
 * manager.createSceneTest1()
 * manager.update()
 * ```
 * 
 * Methods:
 * - `getInstance() -> SceneManager` - Get singleton instance
 * - `createSceneTest1()` - Create test scene
 * - `input()` - Process scene input
 * - `update()` - Update scene
 * - `render()` - Render scene
 * 
 * @section application Game Application
 * 
 * @subsection game_app GameApplication
 * Main game application class.
 * ```python
 * # Create and run game
 * app = engine.GameApplication("My Game")
 * app.m_FPS = 60
 * app.start()
 * app.runLoop()
 * ```
 * 
 * Methods:
 * - `GameApplication(title: str)` - Create game
 * - `start()` - Initialize game
 * - `runLoop()` - Run game loop
 * - `m_FPS: int` - Frames per second
 * - `m_gameIsRunning: bool` - Game running state
 */