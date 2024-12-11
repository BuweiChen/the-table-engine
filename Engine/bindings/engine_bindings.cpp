#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "vec2.h"
#include "component.h"
#include "script.h"
#include "scene.h"
#include "gameobject.h"
// #include "sound.h"
#include "collide.h"
#include "transform.h"
#include "resourcemanager.h"
#include "texture.h"
#include "animation.h"
#include "scenemanager.h"
#include "input.h"
#include "gameapp.h"
#include "gameobjectfactory.h"

#include "projectile_script.h"
#include "ranged_weapon_script.h"
#include "collision_script.h"
#include "enemy_ai_script.h"
#include "player_input_script.h"

namespace py = pybind11;

PYBIND11_MODULE(engine, m) {
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
    m.doc() = "Python bindings for the Game Engine core classes";

    // Bind Vec2 (vec2.h)
    py::class_<Vec2>(m, "Vec2")
        .def(py::init<>())
        .def(py::init<float, float>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__eq__", &Vec2::operator==);

    // Bind Component base class (component.h)
    py::class_<Component>(m, "Component")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("getName", &Component::getName)
        .def("getOwner", &Component::getOwner)
        .def("setName", &Component::setName)
        .def("setOwner", &Component::setOwner)
        .def("input", &Component::input)
        .def("update", &Component::update)
        .def("render", &Component::render);

    // Bind Script (script.h)
    py::class_<Script>(m, "Script")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def_readwrite("m_name", &Script::m_name)
        .def_readwrite("m_owner", &Script::m_owner)
        .def("getName", &Script::getName)
        .def("getOwner", &Script::getOwner)
        .def("setOwner", &Script::setOwner)
        .def("input", &Script::input)
        .def("update", &Script::update)
        .def("render", &Script::render);

    // Bind SceneNode with nodelete since it has a private destructor (scene.h)
    py::class_<SceneNode, std::unique_ptr<SceneNode, py::nodelete>>(m, "SceneNode")
        .def(py::init<GameObject*>())
        .def("addChild", &SceneNode::addChild)
        .def("getChildren", &SceneNode::getChildren)
        .def("getParent", &SceneNode::getParent)
        .def("getGameObject", &SceneNode::getGameObject)
        .def("readyToDestroy", &SceneNode::readyToDestroy)
        .def("setDestroy", &SceneNode::setDestroy)
        .def("isBackground", &SceneNode::isBackground)
        .def("setIsBackground", &SceneNode::setIsBackground);

    // Bind SceneTree (scene.h)
    py::class_<SceneTree>(m, "SceneTree")
        .def(py::init<>())
        .def("addChild", &SceneTree::addChild)
        .def("findGameObjectById", &SceneTree::findGameObjectById)
        .def("findGameObjectsByTag", &SceneTree::findGameObjectsByTag)
        .def("traverseTree", py::overload_cast<std::function<void(SceneNode*)>>(&SceneTree::traverseTree))
        .def("traverseTree", py::overload_cast<SceneNode*, std::function<void(SceneNode*)>>(&SceneTree::traverseTree));

    // Bind GameObject with nodelete since it has a private destructor (gameobject.h)
    py::class_<GameObject, std::unique_ptr<GameObject, py::nodelete>>(m, "GameObject")
        .def(py::init<std::string>())
        .def("getId", &GameObject::getId)
        .def("getTag", &GameObject::getTag)
        .def("getSceneNode", &GameObject::getSceneNode)
        .def("setSceneNode", &GameObject::setSceneNode)
        .def("getChildren", &GameObject::getChildren)
        .def("input", &GameObject::input)
        .def("update", &GameObject::update)
        .def("render", &GameObject::render)
        // Template methods need special handling in Python
        .def("getComponent", [](GameObject &self) {
            return self.getComponent<Component>();
        })
        .def("addComponent", [](GameObject &self, Component* component) {
            self.addComponent<Component>(component);
        })
        .def("getScript", [](GameObject &self) {
            return self.getScript<Script>();
        })
        .def("addScript", [](GameObject &self, Script* script) {
            self.addScript<Script>(script);
        })
        .def("getTexture", [](GameObject &self) {
            return self.getComponent<Texture>();
        })
        .def("addTexture", [](GameObject &self, Texture* texture) {
            self.addComponent<Texture>(texture);
        })
        .def("getCollide", [](GameObject &self) {
            return self.getComponent<Collide>();
        })
        .def("addCollide", [](GameObject &self, Collide* collide) {
            self.addComponent<Collide>(collide);
        })
        .def("getAnimation", [](GameObject &self) {
            return self.getComponent<Animation>();
        })
        .def("addAnimation", [](GameObject &self, Animation* animation) {
            self.addComponent<Animation>(animation);
        });

    // // Bind Sound (sound.h)
    // py::class_<Sound>(m, "Sound")
    //     .def(py::init<std::string>())
    //     .def("play", &Sound::play)
    //     .def("stop", &Sound::stop)
    //     .def("pause", &Sound::pause)
    //     .def("resume", &Sound::resume)
    //     .def("setVolume", &Sound::setVolume);

    // Bind Collide component (collide.h)
    py::class_<Collide, Component>(m, "Collide")
        .def(py::init<>())
        // .def(py::init<int, int, int, int>())
        .def("getScreenPosition", &Collide::getScreenPosition)
        .def("getScreenSize", &Collide::getScreenSize)
        .def("setTransformOffset", &Collide::setTransformOffset)
        .def("setScreenPosition", py::overload_cast<int, int>(&Collide::setScreenPosition))
        .def("setScreenPosition", py::overload_cast<Vec2>(&Collide::setScreenPosition))
        .def("setScreenSize", py::overload_cast<int, int>(&Collide::setScreenSize))
        .def("setScreenSize", py::overload_cast<Vec2>(&Collide::setScreenSize))
        .def("isColliding", py::overload_cast<Collide*>(&Collide::isColliding))
        .def("update", &Collide::update)
        .def("render", &Collide::render);

    py::class_<Transform, Component>(m, "Transform")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def("getScreenRect", &Transform::getScreenRect)
        .def("getWorldPosition", &Transform::getWorldPosition)
        .def("getScreenPosition", &Transform::getScreenPosition)
        .def("getScreenSize", &Transform::getScreenSize)
        .def("setWorldPosition", py::overload_cast<float, float>(&Transform::setWorldPosition))
        .def("setWorldPosition", py::overload_cast<Vec2>(&Transform::setWorldPosition))
        .def("updateWorldPosition", py::overload_cast<float, float>(&Transform::updateWorldPosition))
        .def("updateWorldPosition", py::overload_cast<Vec2>(&Transform::updateWorldPosition))
        .def("setWorldSize", py::overload_cast<float, float>(&Transform::setWorldSize))
        .def("setWorldSize", py::overload_cast<Vec2>(&Transform::setWorldSize))
        .def("render", &Transform::render);

    // Bind Texture component (without exposing SDL types)
    py::class_<Texture, Component>(m, "Texture")
        .def(py::init<>())
        .def("setSizeInSpriteMap", &Texture::setSizeInSpriteMap)
        .def("setPositionInSpriteMap", &Texture::setPositionInSpriteMap)
        .def("setFlipHorizontal", &Texture::setFlipHorizontal)
        .def("setFlipVertical", &Texture::setFlipVertical)
        .def("setAngle", &Texture::setAngle)
        .def("update", &Texture::update)
        .def("render", &Texture::render);

    // Add Animation bindings
    py::class_<Animation, Texture>(m, "Animation")
        .def(py::init<>())
        .def("getRows", &Animation::getRows)
        .def("getCols", &Animation::getCols)
        .def("getNumFrames", &Animation::getNumFrames)
        .def("setAutoPlay", &Animation::setAutoPlay)
        .def("setRowsColsInSpriteMap", &Animation::setRowsColsInSpriteMap)
        .def("setAnimationTime", &Animation::setAnimationTime)
        .def("play", &Animation::play)
        .def("pause", &Animation::pause)
        .def("setFrame", &Animation::setFrame)
        .def("getCurrentFrame", &Animation::getCurrentFrame)
        .def("isPlaying", &Animation::isPlaying)
        .def("update", &Animation::update);


    // SceneManager bindings (without direct SDL type exposure)
    py::class_<SceneManager>(m, "SceneManager")
        .def_static("getInstance", &SceneManager::getInstance, py::return_value_policy::reference)
        .def_readonly_static("m_totalObjects", &SceneManager::m_totalObjects)
        .def_readonly_static("m_aliveObjects", &SceneManager::m_aliveObjects)
        .def("getNextScene", &SceneManager::getNextScene)
        .def("getSceneTree", &SceneManager::getSceneTree, py::return_value_policy::reference)
        .def("cleanTree", &SceneManager::cleanTree)
        .def("createSceneTest1", &SceneManager::createSceneTest1)
        .def("input", &SceneManager::input)
        .def("update", &SceneManager::update)
        .def("render", &SceneManager::render);

    // ResourceManager bindings (without direct SDL type exposure)
    py::class_<ResourceManager>(m, "ResourceManager")
        .def_static("getInstance", &ResourceManager::getInstance, py::return_value_policy::reference);
        // .def("loadSound", &ResourceManager::loadSound, py::return_value_policy::take_ownership);


    // Input component bindings
    py::class_<Input, Component>(m, "Input")
        .def(py::init<>())
        .def_readwrite("spacePressed", &Input::spacePressed)
        .def_readwrite("leftPressed", &Input::leftPressed)
        .def_readwrite("rightPressed", &Input::rightPressed)
        .def_readwrite("upPressed", &Input::upPressed)
        .def_readwrite("downPressed", &Input::downPressed)
        .def_readwrite("m_mouseX", &Input::m_mouseX)
        .def_readwrite("m_mouseY", &Input::m_mouseY)
        .def_readwrite("mouseLeftPressed", &Input::mouseLeftPressed)
        .def_readwrite("mouseRightPressed", &Input::mouseRightPressed)
        .def_readwrite("mouseMiddlePressed", &Input::mouseMiddlePressed)
        .def("update", &Input::update);

    // GameObjectFactory bindings
    py::class_<GameObjectFactory>(m, "GameObjectFactory")
        .def_static("createPlayerTest", &GameObjectFactory::createPlayerTest, py::return_value_policy::reference)
        .def_static("createBow", &GameObjectFactory::createBow, py::return_value_policy::reference)
        .def_static("createArrow", &GameObjectFactory::createArrow, py::return_value_policy::reference)
        .def_static("createEnemyWarrior", &GameObjectFactory::createEnemyWarrior, py::return_value_policy::reference)
        .def_static("createTile1", &GameObjectFactory::createTile1, py::return_value_policy::reference)
        .def_static("createKey", &GameObjectFactory::createKey, py::return_value_policy::reference);

    // GameApplication bindings (avoiding direct SDL type exposure)
    py::class_<GameApplication>(m, "GameApplication")
        .def(py::init<std::string>())
        .def_readwrite("m_gameIsRunning", &GameApplication::m_gameIsRunning)
        .def_readwrite("m_FPS", &GameApplication::m_FPS)
        .def("printStats", &GameApplication::printStats)
        .def("start", &GameApplication::start)
        .def("input", &GameApplication::input)
        .def("update", &GameApplication::update)
        .def("render", &GameApplication::render)
        .def("advanceFrame", &GameApplication::advanceFrame)
        .def("runLoop", &GameApplication::runLoop);



    // Bind ProjectileScript (projectile_script.h)
    py::class_<ProjectileScript, Script>(m, "ProjectileScript")
        .def(py::init<float, float>())
        .def("update", &ProjectileScript::update);

    // Bind Bow_script (ranged_weapon_script.h)
    py::class_<Bow_script, Script>(m, "Bow_script")
        .def(py::init<>())
        .def("input", &Bow_script::input)
        .def("update", &Bow_script::update);

    // Bind CollisionScript (collision_script.h)
    py::class_<CollisionScript, Script>(m, "CollisionScript")
        .def(py::init<>())
        .def("update", &CollisionScript::update)
        .def("render", &CollisionScript::render);

    // Bind EnemyAIScript (enemy_ai_script.h)
    py::class_<EnemyAIScript, Script>(m, "EnemyAIScript")
        .def(py::init<>())
        .def("update", &EnemyAIScript::update);

    // Bind PlayerInputScript (player_input_script.h)
    py::class_<PlayerInputScript, Script>(m, "PlayerInputScript")
        .def(py::init<>())
        .def("getKeysCollected", &PlayerInputScript::getKeysCollected)
        .def("update", &PlayerInputScript::update);
}