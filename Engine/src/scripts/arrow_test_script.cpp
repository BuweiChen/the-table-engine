#include <iostream>

#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"

ArrowTestScript::ArrowTestScript() {
    m_speed = 8;
}

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();

    if (m_owner->getTag() == "left arrow") {
        x -= m_speed;
    } else {
        x += m_speed;
    }

    transform->setPositionInScreen(x, y);
}