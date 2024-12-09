#include <iostream>

#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"

ArrowTestScript::ArrowTestScript() {
    m_speed = 8;
}

ArrowTestScript::ArrowTestScript(std::string dir) : ArrowTestScript() {
    m_dir = dir == "right" ? 1 : -1;
}

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();

    x += m_dir * m_speed;

    if (x < 0 || x > 640) {
        m_owner->getSceneNode()->setDestroy(true);
        return;
    }

    transform->setPositionInScreen(x, y);
}