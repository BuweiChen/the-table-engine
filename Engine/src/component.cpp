#include <string>

#include "component.h"
#include "gameobject.h"

Component::Component() : m_name(""), m_owner(NULL) {}
Component::Component(std::string name) : m_name(name), m_owner(NULL) {}
Component::~Component() {}

std::string Component::GetName() {
    return m_name;
}

GameObject* Component::GetOwner() {
    return m_owner;
}

void Component::SetName(std::string name) {
    m_name = name;
}

void Component::SetOwner(GameObject* owner) {
    m_owner = owner;
}

void Component::Input() {

}

void Component::Update() {

}

void Component::Render() {
    
}
