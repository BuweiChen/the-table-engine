#include <string>

#include "script.h"

Script::Script(std::string name) {
    m_name = name;
}

Script::~Script() {
}

std::string Script::getName() {
    return m_name;
}

GameObject* Script::getOwner() {
    return m_owner;
}

void Script::setOwner(GameObject* owner) {
    m_owner = owner;
}

void Script::input() {
}

void Script::update() {
}

void Script::render() {
}