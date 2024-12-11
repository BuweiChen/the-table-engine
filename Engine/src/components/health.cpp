#include <iostream>

#include "health.h"

Health::Health() : m_currentHealth(1000) {
    setName("Health");
}

Health::~Health() {
    return;
}

void Health::updateHealth(int amount) {
    m_currentHealth += amount;
}

int Health::getHealth() {
    return m_currentHealth;
}
