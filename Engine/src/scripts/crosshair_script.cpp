#include "crosshair_script.h"
#include "input.h"
#include "transform.h"
#include "scenemanager.h"

void CrosshairScript::update() {
    auto input = m_owner->getComponent<Input>();
    auto transform = m_owner->getComponent<Transform>();
    auto cameraPosition = SceneManager::getInstance().getCameraWorldPosition();

    if (input && transform) {
        int worldMouseX = input->m_mouseX + cameraPosition.x - 320;
        int worldMouseY = input->m_mouseY + cameraPosition.y - 240;
        transform->setWorldPosition(worldMouseX, worldMouseY);
    }
}
