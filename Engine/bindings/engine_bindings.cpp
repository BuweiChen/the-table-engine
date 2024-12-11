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
#include "animationsmanager.h"
#include "camera.h"
#include "crosshair_script.h"
#include "health.h"

namespace py = pybind11;

PYBIND11_MODULE(engine, m) {
    m.doc() = "Python bindings for the Game Engine core classes";

    py::class_<Vec2>(m, "Vec2")
        .def(py::init<>())
        .def(py::init<float, float>())
        .def_readwrite("x", &Vec2::x)
        .def_readwrite("y", &Vec2::y)
        .def("__eq__", &Vec2::operator==);

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

    py::class_<SceneTree>(m, "SceneTree")
        .def(py::init<>())
        .def("addChild", &SceneTree::addChild)
        .def("findGameObjectById", &SceneTree::findGameObjectById)
        .def("findGameObjectsByTag", &SceneTree::findGameObjectsByTag)
        .def("traverseTree", py::overload_cast<std::function<void(SceneNode*)>>(&SceneTree::traverseTree))
        .def("traverseTree", py::overload_cast<SceneNode*, std::function<void(SceneNode*)>>(&SceneTree::traverseTree));

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

    py::class_<Collide, Component>(m, "Collide")
        .def(py::init<>())
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
        .def("update", &Transform::update);

    py::class_<Texture, Component>(m, "Texture")
        .def(py::init<>())
        .def("setSizeInSpriteMap", &Texture::setSizeInSpriteMap)
        .def("setPositionInSpriteMap", &Texture::setPositionInSpriteMap)
        .def("setFlipHorizontal", &Texture::setFlipHorizontal)
        .def("setFlipVertical", &Texture::setFlipVertical)
        .def("setAngle", &Texture::setAngle)
        .def("update", &Texture::update)
        .def("render", &Texture::render);

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


    py::class_<SceneManager>(m, "SceneManager")
        .def_static("getInstance", &SceneManager::getInstance, py::return_value_policy::reference)
        .def_readonly_static("m_totalObjects", &SceneManager::m_totalObjects)
        .def_readonly_static("m_aliveObjects", &SceneManager::m_aliveObjects)
        .def("loadDemo", &SceneManager::loadDemo)
        .def("loadScenesFromJSON", &SceneManager::loadScenesFromJSON)
        .def("getNextScene", &SceneManager::getNextScene)
        .def("getSceneIndex", &SceneManager::getSceneIndex)
        .def("getSceneTree", &SceneManager::getSceneTree, py::return_value_policy::reference)
        .def("cleanTree", &SceneManager::cleanTree)
        .def("getCameraWorldPosition", &SceneManager::getCameraWorldPosition)
        .def("createSceneTest1", &SceneManager::createSceneTest1)
        .def("createSceneTest2", &SceneManager::createSceneTest2)
        .def("createSceneTest3", &SceneManager::createSceneTest3)
        .def("input", &SceneManager::input)
        .def("update", &SceneManager::update)
        .def("render", &SceneManager::render);

    py::class_<ResourceManager>(m, "ResourceManager")
        .def_static("getInstance", &ResourceManager::getInstance, py::return_value_policy::reference);
        // .def("loadSound", &ResourceManager::loadSound, py::return_value_policy::take_ownership);

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

    py::class_<GameObjectFactory>(m, "GameObjectFactory")
        .def_static("createPlayerTest", &GameObjectFactory::createPlayerTest, py::return_value_policy::reference)
        .def_static("createBow", &GameObjectFactory::createBow, py::return_value_policy::reference)
        .def_static("createArrow", py::overload_cast<int, int>(&GameObjectFactory::createArrow), py::return_value_policy::reference)
        .def_static("createEnemyWarrior", &GameObjectFactory::createEnemyWarrior, py::return_value_policy::reference)
        .def_static("createEnemyWarriorCustom", &GameObjectFactory::createEnemyWarriorCustom, py::return_value_policy::reference)
        .def_static("createTile1", &GameObjectFactory::createTile1, py::return_value_policy::reference)
        .def_static("createTileCustom", &GameObjectFactory::createTileCustom, py::return_value_policy::reference)
        .def_static("createWallCustom", &GameObjectFactory::createWallCustom, py::return_value_policy::reference)
        .def_static("createTableCustom", &GameObjectFactory::createTableCustom, py::return_value_policy::reference)
        .def_static("createKey", &GameObjectFactory::createKey, py::return_value_policy::reference)
        .def_static("createCrosshair", &GameObjectFactory::createCrosshair, py::return_value_policy::reference);

    py::class_<GameApplication>(m, "GameApplication")
        .def(py::init<std::string>())
        .def_readwrite("m_gameIsRunning", &GameApplication::m_gameIsRunning)
        .def_readwrite("m_FPS", &GameApplication::m_FPS)
        .def("printStats", &GameApplication::printStats)
        .def("start", &GameApplication::start, py::arg("demo")) 
        .def("input", &GameApplication::input)
        .def("update", &GameApplication::update)
        .def("render", &GameApplication::render)
        .def("advanceFrame", &GameApplication::advanceFrame)
        .def("runLoop", &GameApplication::runLoop);

    py::class_<ProjectileScript, Script>(m, "ProjectileScript")
        .def(py::init<float, float>())
        .def("update", &ProjectileScript::update);

    py::class_<RangedWeaponScript, Script>(m, "RangedWeaponScript")
        .def(py::init<>())
        .def("input", &RangedWeaponScript::input)
        .def("update", &RangedWeaponScript::update);

    py::class_<CollisionScript, Script>(m, "CollisionScript")
        .def(py::init<>())
        .def("update", &CollisionScript::update)
        .def("render", &CollisionScript::render);

    py::class_<EnemyAIScript, Script>(m, "EnemyAIScript")
        .def(py::init<>())
        .def("update", &EnemyAIScript::update);

    py::class_<PlayerInputScript, Script>(m, "PlayerInputScript")
        .def(py::init<>())
        .def("getKeysCollected", &PlayerInputScript::getKeysCollected)
        .def("update", &PlayerInputScript::update);

    py::class_<Camera, Component>(m, "Camera")
        .def(py::init<>())
        .def("getWorldPosition", &Camera::getWorldPosition)
        .def("setWorldPosition", &Camera::setWorldPosition)
        .def("update", &Camera::update);

    py::class_<AnimationsManager, Texture>(m, "AnimationsManager")
        .def(py::init<>())
        .def("addAnimation", [](AnimationsManager& self, Animation* animation) {
            return self.addAnimation(animation);
        })
        .def("setCurrentAnimation", &AnimationsManager::setCurrentAnimation)
        .def("getCurrentAnimationObject", &AnimationsManager::getCurrentAnimationObject)
        .def("play", &AnimationsManager::play)
        .def("pause", &AnimationsManager::pause)
        .def("setFrame", &AnimationsManager::setFrame)
        .def("getCurrentFrame", &AnimationsManager::getCurrentFrame)
        .def("isPlaying", &AnimationsManager::isPlaying)
        .def("update", &AnimationsManager::update)
        .def("render", &AnimationsManager::render)
        .def("setSizeInSpriteMap", &AnimationsManager::setSizeInSpriteMap)
        .def("setPositionInSpriteMap", &AnimationsManager::setPositionInSpriteMap)
        .def("setFlipHorizontal", &AnimationsManager::setFlipHorizontal)
        .def("setFlipVertical", &AnimationsManager::setFlipVertical)
        .def("setAngle", &AnimationsManager::setAngle);

     py::class_<Health, Component>(m, "Health")
        .def(py::init<>())
        .def(py::init<int>())
        .def("getHealth", &Health::getHealth)
        .def("updateHealth", &Health::updateHealth);
    
}