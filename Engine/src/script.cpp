#include <string>

#include "script.h"

Script::Script(std::string name) {
    m_name = name;
}

Script::~Script() {
}

std::string Script::GetName() {
    return m_name;
}

GameObject* Script::GetOwner() {
    return m_owner;
}

void Script::SetOwner(GameObject* owner) {
    m_owner = owner;
}

void Script::Input() {
}

void Script::Update() {
}

void Script::Render() {
}