#pragma once

/**
 * @file vec2.h
 * @brief Definition of Vec2 structure for 2D vector operations.
 *
 * Provides basic functionality for 2D vector operations used within the Game Engine.
 */

/**
 * @struct Vec2
 * @brief A structure to represent 2D vectors.
 *
 * This structure is used throughout the Game Engine to handle 2-dimensional vector operations.
 */
struct Vec2 {
    float x; ///< X coordinate of the vector.
    float y; ///< Y coordinate of the vector.

    /**
     * @brief Default constructor initializing vector to (0, 0).
     */
    Vec2() : x(0), y(0) {}

    /**
     * @brief Constructor that initializes vector with specified x and y values.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    Vec2(float x, float y) : x(x), y(y) {}

    /**
     * @brief Checks equality of this vector with another vector.
     * @param other The vector to compare with.
     * @return true if the vectors are equal, false otherwise.
     */
    bool operator==(const Vec2& other) const 
    {
        return x == other.x && y == other.y;
    }
};
