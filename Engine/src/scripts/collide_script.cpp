#include <iostream>

#include "collide_script.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "collide.h"
#include "transform.h"

CollideScript::CollideScript() {
    
}

void CollideScript::update() {
    // update object collide rect to match object transform
    auto collide = m_owner->getComponent<Collide>();
    auto transform = m_owner->getComponent<Transform>();
    collide->setPositionInScreen(transform->getPositionX(), transform->getPositionY());
}