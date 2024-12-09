#include <string>
#include <iostream>

#include "component.h"
#include "gameobject.h"

Component::Component() : m_name(""), m_owner(NULL) {}
Component::Component(std::string name) : m_name(name), m_owner(NULL) {}
Component::~Component() {}

std::string Component::getName() {
    return m_name;
}

GameObject* Component::getOwner() {
    return m_owner;
}

void Component::setName(std::string name) {
    m_name = name;
}

void Component::setOwner(GameObject* owner) {
    m_owner = owner;
}

void Component::input() {

}

void Component::update() {

}

void Component::render() {
    
}
