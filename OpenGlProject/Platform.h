#ifndef PLATFORM_H
#define PLATFORM_H

#include "Circle.h"
#include "CustomShape.h"  // Include the CustomShape class header

class Platform {
public:
    float x, y;  // Position
    float width, height;
    float vx, vy;  // Velocity

    Platform(float x, float y, float width, float height, float vx, float vy);

    void update(float dt);

    void draw() const;

    bool isCircleCollision(const Circle& circle) const;

    void resolveCircleCollision(Circle& circle);

    bool isCustomShapeCollision(const CustomShape& customShape) const;

    void resolveCustomShapeCollision(CustomShape& customShape);

    void Movement(int key, int action,int maxX, int maxY);
};

#endif // PLATFORM_H
