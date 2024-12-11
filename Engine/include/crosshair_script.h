#include "script.h"

/**
 * @class CrosshairScript
 * @brief Script for managing the crosshair in the game.
 *
 * This script updates the position of the crosshair to follow the mouse cursor.
 */
class CrosshairScript : public Script {
public:
    /**
     * @brief Updates the position of the crosshair based on the mouse cursor.
     */
    void update() override;
};