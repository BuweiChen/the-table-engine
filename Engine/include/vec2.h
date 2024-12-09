#pragma once

struct Vec2 {
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
};