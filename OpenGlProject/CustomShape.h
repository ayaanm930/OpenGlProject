#ifndef CUSTOMSHAPE_H
#define CUSTOMSHAPE_H

#include "Circle.h"  // Include the Circle class header

class CustomShape {
public:
    float x, y;  // Position
    float width, height;
    float vx, vy;  // Velocity
    float ax, ay;  // Acceleration
    float mass;    // Mass of the shape
    
    CustomShape(float x, float y, float width, float height, float vx, float vy, float ax, float ay, float mass);

    // Update shape position, velocity, and acceleration
    void update(float dt);

    void draw() const;

    // Check collision with a circle
    bool isCircleCollision(const Circle& circle) const;

    // Resolve collision with a circle
    void resolveCircleCollision(Circle& circle);
};

#endif // CUSTOMSHAPE_H
