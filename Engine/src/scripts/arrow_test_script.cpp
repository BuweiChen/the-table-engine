#include <iostream>

#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"

ArrowTestScript::ArrowTestScript(int dx, int dy) {
    m_dx = dx / 20;
    m_dy = dy / 20;
}

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();

    x += m_dx;
    y += m_dy;

    if (x < 0 || x > 640 || y < 0 || y > 480) {
        m_owner->getSceneNode()->markForDeletion();
        return;
    }

    transform->setPositionInScreen(x, y);
}