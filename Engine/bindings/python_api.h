/**
 * @file python_api.h
 * @brief Complete documentation for the Game Engine Python API
 * 
 * @page Python Bindings API
 * 
 * @tableofcontents
 * 
 * @section overview Overview
 * Comprehensive documentation for all classes and methods available in the Python API.
 * The API provides access to the game engine's core functionality including:
 * - Core utilities (vectors, components)
 * - Game objects and scene management
 * - Input handling and physics
 * - Graphics and animation
 * - Game logic and scripting
 * 
 * @section core Core Classes
 * 
 * @subsection vec2 Vec2
 * 2D Vector class for positions and sizes
 * ```python
 * pos = engine.Vec2(100.0, 200.0)
 * ```
 * Members:
 * - `x: float` - X coordinate
 * - `y: float` - Y coordinate
 * 
 * Methods:
 * - `Vec2()` - Create zero vector (0,0)
 * - `Vec2(x: float, y: float)` - Create vector with coordinates
 * - `__eq__(other: Vec2) -> bool` - Compare vectors for equality
 * 
 * @subsection component Component
 * Base class for all game object components
 * ```python
 * comp = engine.Component("myComponent")
 * ```
 * Methods:
 * - `Component()` - Create unnamed component
 * - `Component(name: str)` - Create named component
 * - `getName() -> str` - Get component name
 * - `getOwner() -> GameObject` - Get owning game object
 * - `setName(name: str)` - Set component name
 * - `setOwner(owner: GameObject)` - Set owning object
 * - `input()` - Process input
 * - `update()` - Update component state
 * - `render()` - Render component
 * 
 * @section objects Game Objects
 * 
 * @subsection gameobject GameObject
 * Base class for all entities in the game
 * ```python
 * obj = engine.GameObject("player")
 * obj.addComponent(engine.Transform(100, 100))
 * ```
 * Methods:
 * - `GameObject(tag: str)` - Create object with tag
 * - `getId() -> str` - Get unique identifier
 * - `getTag() -> str` - Get object tag
 * - `getSceneNode() -> SceneNode` - Get scene graph node
 * - `setSceneNode(node: SceneNode)` - Set scene graph node
 * - `getChildren() -> list[GameObject]` - Get child objects
 * - `input()` - Process input
 * - `update()` - Update object state
 * - `render()` - Render object
 * Component Methods:
 * - `getComponent(type) -> Component` - Get component by type
 * - `addComponent(component: Component)` - Add component
 * - `getTexture() -> Texture` - Get texture component
 * - `addTexture(texture: Texture)` - Add texture component
 * - `getCollide() -> Collide` - Get collision component
 * - `addCollide(collide: Collide)` - Add collision component
 * - `getAnimation() -> Animation` - Get animation component
 * - `addAnimation(animation: Animation)` - Add animation component
 * Script Methods:
 * - `getScript(type) -> Script` - Get script by type
 * - `addScript(script: Script)` - Add script component
 * 
 * @section components Component Types
 * 
 * @subsection transform Transform
 * Handles position and size in world space
 * ```python
 * transform = engine.Transform(100, 100)
 * transform.setWorldPosition(50, 50)
 * ```
 * Methods:
 * - `Transform()` - Create at origin
 * - `Transform(x: int, y: int)` - Create at position
 * - `getScreenRect() -> SDL_Rect` - Get screen rectangle
 * - `getWorldPosition() -> Vec2` - Get world position
 * - `getScreenPosition() -> Vec2` - Get screen position
 * - `getScreenSize() -> Vec2` - Get screen size
 * - `setWorldPosition(x: float, y: float)` - Set world position
 * - `setWorldPosition(pos: Vec2)` - Set world position
 * - `updateWorldPosition(dx: float, dy: float)` - Update position
 * - `updateWorldPosition(delta: Vec2)` - Update position
 * - `setWorldSize(w: float, h: float)` - Set world size
 * - `setWorldSize(size: Vec2)` - Set world size
 * - `update()` - Update transform
 * 
 * @subsection collide Collide
 * Handles collision detection and response
 * ```python
 * collider = engine.Collide()
 * collider.setScreenSize(32, 32)
 * ```
 * Methods:
 * - `Collide()` - Create collider
 * - `getScreenPosition() -> Vec2` - Get screen position
 * - `getScreenSize() -> Vec2` - Get screen size
 * - `setTransformOffset(x: int, y: int)` - Set offset from transform
 * - `setScreenPosition(x: int, y: int)` - Set screen position
 * - `setScreenPosition(pos: Vec2)` - Set screen position
 * - `setScreenSize(w: int, h: int)` - Set screen size 
 * - `setScreenSize(size: Vec2)` - Set screen size
 * - `isColliding(other: Collide) -> bool` - Check collision
 * - `update()` - Update collider
 * - `render()` - Debug render collider
 * 
 * @subsection health Health
 * Manages entity health/damage
 * ```python
 * health = engine.Health(100)  # 100 HP
 * health.updateHealth(-10)     # Take 10 damage
 * ```
 * Methods:
 * - `Health()` - Create with default health
 * - `Health(health: int)` - Create with specified health
 * - `getHealth() -> int` - Get current health
 * - `updateHealth(amount: int)` - Modify health by amount
 * 
 * @section graphics Graphics Components
 * 
 * @subsection texture Texture
 * Base class for rendering textures and sprites
 * ```python
 * texture = engine.Texture()
 * texture.setSizeInSpriteMap(32, 32)
 * ```
 * Methods:
 * - `Texture()` - Create texture
 * - `setSizeInSpriteMap(w: int, h: int)` - Set size in sprite sheet
 * - `setPositionInSpriteMap(x: int, y: int)` - Set position in sprite sheet
 * - `setFlipHorizontal(flip: bool)` - Set horizontal flip
 * - `setFlipVertical(flip: bool)` - Set vertical flip
 * - `setAngle(angle: float)` - Set rotation angle
 * - `update()` - Update texture
 * - `render()` - Render texture
 * 
 * @subsection animation Animation
 * Handles sprite sheet animations
 * ```python
 * anim = engine.Animation()
 * anim.setRowsColsInSpriteMap(1, 8)  # 8 frame animation
 * anim.setAnimationTime(0.5)         # 0.5s per cycle
 * anim.play()
 * ```
 * Methods:
 * - `Animation()` - Create animation
 * - `getRows() -> int` - Get rows in sprite sheet
 * - `getCols() -> int` - Get columns in sprite sheet 
 * - `getNumFrames() -> int` - Get total frame count
 * - `setAutoPlay(autoplay: bool)` - Set auto-play state
 * - `setRowsColsInSpriteMap(rows: int, cols: int)` - Set sprite sheet layout
 * - `setAnimationTime(time: float)` - Set animation cycle time
 * - `play()` - Start/resume animation
 * - `pause()` - Pause animation
 * - `setFrame(frame: int)` - Set current frame
 * - `getCurrentFrame() -> int` - Get current frame
 * - `isPlaying() -> bool` - Check if playing
 * - `update()` - Update animation state
 * 
 * @subsection animations_manager AnimationsManager
 * Manages multiple animations for an entity
 * ```python
 * manager = engine.AnimationsManager()
 * manager.addAnimation(idle_anim)
 * manager.setCurrentAnimation(0)
 * manager.play()
 * ```
 * Methods:
 * - `AnimationsManager()` - Create manager
 * - `addAnimation(animation: Animation) -> int` - Add animation
 * - `setCurrentAnimation(index: int)` - Switch animation
 * - `getCurrentAnimationObject() -> Animation` - Get current animation
 * - `play()` - Play current animation
 * - `pause()` - Pause current animation
 * - `setFrame(frame: int)` - Set current frame
 * - `getCurrentFrame() -> int` - Get current frame
 * - `isPlaying() -> bool` - Check if playing
 * - `update()` - Update animation state
 * - `render()` - Render current animation
 * Inherited from Texture:
 * - `setSizeInSpriteMap(w: int, h: int)`
 * - `setPositionInSpriteMap(x: int, y: int)`
 * - `setFlipHorizontal(flip: bool)`
 * - `setFlipVertical(flip: bool)` 
 * - `setAngle(angle: float)`
 * 
 * @section input Input Handling
 * 
 * @subsection input Input
 * Handles keyboard and mouse input
 * ```python
 * input = engine.Input()
 * if input.spacePressed:
 *     jump()
 * ```
 * Properties:
 * - `spacePressed: bool` - Space key state
 * - `leftPressed: bool` - Left arrow key state
 * - `rightPressed: bool` - Right arrow key state
 * - `upPressed: bool` - Up arrow key state
 * - `downPressed: bool` - Down arrow key state
 * - `m_mouseX: int` - Mouse X position
 * - `m_mouseY: int` - Mouse Y position
 * - `mouseLeftPressed: bool` - Left mouse button state
 * - `mouseRightPressed: bool` - Right mouse button state
 * - `mouseMiddlePressed: bool` - Middle mouse button state
 * Methods:
 * - `Input()` - Create input handler
 * - `update()` - Update input states
 * 
 * @section scripts Script Components
 * 
 * @subsection script Script
 * Base class for game object behaviors
 * ```python
 * script = engine.Script("myScript")
 * ```
 * Properties:
 * - `m_name: str` - Script name
 * - `m_owner: GameObject` - Owning game object
 * Methods:
 * - `Script()` - Create unnamed script
 * - `Script(name: str)` - Create named script
 * - `getName() -> str` - Get script name
 * - `getOwner() -> GameObject` - Get owning object
 * - `setOwner(owner: GameObject)` - Set owning object
 * - `input()` - Process input
 * - `update()` - Update script
 * - `render()` - Render debug info
 * 
 * @subsection player_script PlayerInputScript
 * Handles player character controls
 * ```python
 * player.addScript(engine.PlayerInputScript())
 * ```
 * Methods:
 * - `PlayerInputScript()` - Create player controller
 * - `getKeysCollected() -> int` - Get collected key count
 * - `update()` - Update player state
 * 
 * @subsection projectile_script ProjectileScript  
 * Controls projectile movement
 * ```python
 * arrow.addScript(engine.ProjectileScript(10, 0))  # Right-moving
 * ```
 * Methods:
 * - `ProjectileScript(dx: float, dy: float)` - Create with velocity
 * - `update()` - Update projectile position
 * 
 * @subsection weapon_script RangedWeaponScript
 * Handles ranged weapon firing
 * ```python
 * bow.addScript(engine.RangedWeaponScript())
 * ```
 * Methods:
 * - `RangedWeaponScript()` - Create weapon controller
 * - `input()` - Handle firing input
 * - `update()` - Update weapon state
 * 
 * @subsection collision_script CollisionScript
 * Handles collision responses
 * ```python
 * obj.addScript(engine.CollisionScript())
 * ```
 * Methods:
 * - `CollisionScript()` - Create collision handler
 * - `update()` - Handle collisions
 * - `render()` - Debug render
 * 
 * @subsection enemy_script EnemyAIScript
 * Controls enemy AI behavior
 * ```python
 * enemy.addScript(engine.EnemyAIScript())
 * ```
 * Methods:
 * - `EnemyAIScript()` - Create enemy AI
 * - `update()` - Update AI behavior
 * 
 * @section scene Scene Management
 * 
 * @subsection scene_node SceneNode
 * Node in scene graph hierarchy
 * ```python
 * node = engine.SceneNode(gameObject)  
 * node.addChild(childObject)
 * ```
 * Methods:
 * - `SceneNode(gameObject: GameObject)` - Create node
 * - `addChild(child: GameObject, isBackground: bool = False)` - Add child
 * - `getChildren() -> list[SceneNode]` - Get child nodes
 * - `getParent() -> SceneNode` - Get parent node
 * - `getGameObject() -> GameObject` - Get game object
 * - `readyToDestroy() -> bool` - Check if marked for destruction
 * - `setDestroy(destroy: bool)` - Mark for destruction
 * - `isBackground() -> bool` - Check if background
 * - `setIsBackground(isBackground: bool)` - Set background state
 * 
 * @subsection scene_tree SceneTree
 * Manages scene graph hierarchy
 * ```python
 * tree = engine.SceneTree()
 * tree.addChild(rootObject)
 * ```
 * Methods:
 * - `SceneTree()` - Create scene tree
 * - `addChild(child: GameObject, isBackground: bool = False)` - Add root object
 * - `findGameObjectById(id: str) -> GameObject` - Find by ID
 * - `findGameObjectsByTag(tag: str) -> list[GameObject]` - Find by tag
 * - `traverseTree(callback: function)` - Visit all nodes
 * - `traverseTree(node: SceneNode, callback: function)` - Visit from node
 * 
 * @subsection camera Camera
 * Controls game view/camera
 * ```python
 * camera = engine.Camera()
 * camera.setWorldPosition(100, 100)
 * ```
 * Methods:
 * - `Camera()` - Create camera
 * - `getWorldPosition() -> Vec2` - Get position
 * - `setWorldPosition(x: float, y: float)` - Set position
 * - `update()` - Update camera
 * 
 * @section managers Manager Classes
 * 
/**
 * @subsection scene_manager SceneManager
 * Singleton manager controlling game scenes and object lifecycles
 * ```python
 * manager = engine.SceneManager.getInstance()
 * manager.createSceneTest1()
 * manager.update()
 * ```
 * Static Properties:
 * - `m_totalObjects: int` - Total objects created since startup
 * - `m_aliveObjects: int` - Currently active objects
 *
 * Methods:
 * - `getInstance() -> SceneManager` - Get singleton instance
 * - `loadDemo()` - Load demo scene
 * - `loadScenesFromJSON(path: str)` - Load scenes from JSON file
 * - `getNextScene()` - Switch to next scene
 * - `getSceneIndex() -> int` - Get current scene index
 * - `getSceneTree() -> SceneTree` - Get current scene tree
 * - `cleanTree()` - Remove destroyed objects
 * - `getCameraWorldPosition() -> Vec2` - Get camera position
 * - `createSceneTest1() -> SceneTree` - Create test scene 1
 * - `createSceneTest2() -> SceneTree` - Create test scene 2
 * - `createSceneTest3() -> SceneTree` - Create test scene 3
 * - `input()` - Process scene input
 * - `update()` - Update scene state
 * - `render()` - Render scene
 *
 * @subsection resource_manager ResourceManager
 * Singleton manager handling game resources like textures and sounds
 * ```python
 * manager = engine.ResourceManager.getInstance()
 * ```
 * Methods:
 * - `getInstance() -> ResourceManager` - Get singleton instance
 *
 * @section app Game Application
 * 
 * @subsection game_app GameApplication
 * Main game application class handling core game loop
 * ```python
 * app = engine.GameApplication("My Game")
 * app.start(False)  # Start in normal mode
 * app.runLoop()
 * ```
 * Properties:
 * - `m_gameIsRunning: bool` - Game running state
 * - `m_FPS: float` - Target frames per second
 *
 * Methods:
 * - `GameApplication(title: str)` - Create game with window title
 * - `printStats()` - Print performance statistics
 * - `start(demo: bool)` - Initialize game (demo=True for demo mode)
 * - `input()` - Process game input
 * - `update()` - Update game state
 * - `render()` - Render game frame
 * - `advanceFrame()` - Advance to next frame
 * - `runLoop()` - Run main game loop
 * 
 * @section factories Factory Classes
 * 
 * @subsection object_factory GameObjectFactory
 * Static factory class for creating game objects
 * ```python
 * player = engine.GameObjectFactory.createPlayerTest()
 * enemy = engine.GameObjectFactory.createEnemyWarrior()
 * ```
 * Static Methods:
 * - `createPlayerTest() -> GameObject` - Create player character
 * - `createBow() -> GameObject` - Create bow weapon
 * - `createArrow(dx: int, dy: int) -> GameObject` - Create arrow projectile
 * - `createEnemyWarrior() -> GameObject` - Create basic enemy
 * - `createEnemyWarriorCustom(path: str, row: int, col: int, animTime: float, 
 *                            pos_x: int, pos_y: int, size_x: int, size_y: int) -> GameObject`
 *   Create customized enemy
 * - `createTile1() -> GameObject` - Create basic tile
 * - `createTileCustom(path: str, pos: Vec2, size: Vec2, 
 *                     sprite_size: Vec2, sprite_pos: Vec2) -> GameObject`
 *   Create customized tile
 * - `createWallCustom(path: str, pos: Vec2, size: Vec2,
 *                     sprite_size: Vec2, sprite_pos: Vec2) -> GameObject`
 *   Create customized wall
 * - `createTableCustom(path: str, pos: Vec2, size: Vec2,
 *                      sprite_size: Vec2, sprite_pos: Vec2) -> GameObject`
 *   Create customized table
 * - `createKey() -> GameObject` - Create collectible key
 * - `createCrosshair() -> GameObject` - Create targeting crosshair
 *
 * @section examples Usage Examples
 *
 * @subsection example_basic Basic Game Setup
 * ```python
 * import engine
 * 
 * # Initialize game
 * app = engine.GameApplication("My Game")
 * app.start(False)
 * 
 * # Create player
 * player = engine.GameObjectFactory.createPlayerTest()
 * 
 * # Add custom behavior
 * player.addScript(engine.PlayerInputScript())
 * 
 * # Game loop
 * while app.m_gameIsRunning:
 *     app.input()
 *     app.update()
 *     app.render()
 *     app.advanceFrame()
 * ```
 *
 * @subsection example_scene Scene Creation
 * ```python
 * # Get scene manager
 * manager = engine.SceneManager.getInstance()
 * 
 * # Create background
 * for x in range(10):
 *     for y in range(10):
 *         tile = engine.GameObjectFactory.createTile1()
 *         transform = tile.getComponent(engine.Transform)
 *         transform.setWorldPosition(x * 32, y * 32)
 * 
 * # Create animated enemy
 * enemy = engine.GameObjectFactory.createEnemyWarrior()
 * enemy_transform = enemy.getComponent(engine.Transform)
 * enemy_transform.setWorldPosition(300, 200)
 * ```
 */