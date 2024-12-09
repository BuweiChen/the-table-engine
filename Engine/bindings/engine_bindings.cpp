#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "gameapp.h"
#include "gameobject.h"
#include "gameobjectfactory.h"
#include "scene.h"
#include "scenemanager.h"
#include "resourcemanager.h"
#include "component.h"
#include "transform.h"
#include "texture.h"
#include "script.h"

namespace py = pybind11;

PYBIND11_MODULE(engine, m) {
    m.doc() = "Python bindings for the complete Game Engine";

    // Bind Component base class
    py::class_<Component>(m, "Component")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("getName", &Component::getName)
        .def("getOwner", &Component::getOwner)
        .def("setName", &Component::setName)
        .def("setOwner", &Component::setOwner)
        .def("update", &Component::update)
        .def("render", &Component::render);

    // Bind Transform component
    py::class_<Transform, Component>(m, "Transform")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def("getWorldPositionX", &Transform::getWorldPositionX)
        .def("getWorldPositionY", &Transform::getWorldPositionY)
        .def("getSizeW", &Transform::getSizeW)
        .def("getSizeH", &Transform::getSizeH)
        .def("setPosition", &Transform::setPosition)
        .def("setSize", &Transform::setSize);

    // Bind Texture component
    py::class_<Texture, Component>(m, "Texture")
        .def(py::init<>())
        .def("render", &Texture::render);

    // Bind Script
    py::class_<Script>(m, "Script")
        .def(py::init<std::string>())
        .def("getName", &Script::getName)
        .def("getOwner", &Script::getOwner)
        .def("setOwner", &Script::setOwner)
        .def("update", &Script::update);

    // Bind GameObject
    py::class_<GameObject>(m, "GameObject")
        .def(py::init<std::string>())
        .def("getId", &GameObject::getId)
        .def("getTag", &GameObject::getTag)
        .def("update", &GameObject::update)
        .def("render", &GameObject::render);

    // Bind GameObjectFactory
    py::class_<GameObjectFactory>(m, "GameObjectFactory")
        .def(py::init<>())
        .def_static("createPlayerTest", &GameObjectFactory::createPlayerTest);

    // Bind SceneManager (Singleton)
    py::class_<SceneManager>(m, "SceneManager")
        .def_static("getInstance", &SceneManager::getInstance, py::return_value_policy::reference)
        .def("update", &SceneManager::update)
        .def("render", &SceneManager::render);

    // Bind ResourceManager (Singleton)
    py::class_<ResourceManager>(m, "ResourceManager")
        .def_static("getInstance", &ResourceManager::getInstance, py::return_value_policy::reference);

    // Bind GameApplication - the main class we'll use for testing
    py::class_<GameApplication>(m, "GameApplication")
        .def(py::init<std::string>())
        .def("start", &GameApplication::start)
        .def("runLoop", &GameApplication::runLoop)
        .def("update", &GameApplication::update)
        .def("render", &GameApplication::render);
}