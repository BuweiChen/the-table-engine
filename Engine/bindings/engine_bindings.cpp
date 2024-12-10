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
#include "scenemanager.h"
#include "input.h"
#include "gameapp.h"
#include "gameobjectfactory.h"

#include "arrow_test_script.h"
#include "bow_script.h"
#include "collide_script.h"
#include "collide_test_script.h"
#include "enemy_ai_script.h"
#include "player_test_script.h"

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>




namespace py = pybind11;

PYBIND11_MODULE(engine, m) {
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
        .def("setRowsColsInSpriteMap", &Texture::setRowsColsInSpriteMap)
        .def("setAnimationTime", &Texture::setAnimationTime)
        .def("setFlipHorizontal", &Texture::setFlipHorizontal)
        .def("setFlipVertical", &Texture::setFlipVertical)
        .def("update", &Texture::update)
        .def("render", &Texture::render);

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



    // Bind ArrowTestScript (arrow_test_script.h)
    py::class_<ArrowTestScript, Script>(m, "ArrowTestScript")
        .def(py::init<float, float>())
        .def("update", &ArrowTestScript::update);

    // Bind Bow_script (bow_script.h)
    py::class_<Bow_script, Script>(m, "Bow_script")
        .def(py::init<>())
        .def("input", &Bow_script::input)
        .def("update", &Bow_script::update);

    // // Bind CollideScript (collide_script.h)
    // py::class_<CollideScript, Script>(m, "CollideScript")
    //     .def(py::init<>())
    //     .def("update", &CollideScript::update);

    // Bind CollideTestScript (collide_test_script.h)
    py::class_<CollideTestScript, Script>(m, "CollideTestScript")
        .def(py::init<>())
        .def("update", &CollideTestScript::update)
        .def("render", &CollideTestScript::render);

    // Bind EnemyAIScript (enemy_ai_script.h)
    py::class_<EnemyAIScript, Script>(m, "EnemyAIScript")
        .def(py::init<>())
        .def("update", &EnemyAIScript::update);

    // Bind PlayerTestScript (player_test_script.h)
    py::class_<PlayerTestScript, Script>(m, "PlayerTestScript")
        .def(py::init<>())
        .def("getKeysCollected", &PlayerTestScript::getKeysCollected)
        .def("update", &PlayerTestScript::update);
}