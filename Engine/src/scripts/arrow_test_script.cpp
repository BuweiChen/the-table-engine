#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();

    if (m_owner->getTag() == "left arrow") {
        x -= 1;
    } else {
        x += 1;
    }

    transform->setPositionInScreen(x, y);
}