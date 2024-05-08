#include "Platform.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

Platform::Platform(float x, float y, float width, float height, float vx, float vy)
    : x(x), y(y), width(width), height(height), vx(vx), vy(vy) {}

void Platform::update(float dt) {
    y += vy * dt;
}

void Platform::draw() const {
    glColor3f(0.0f, 1.0f, 1.0f);  // Cyan color
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

bool Platform::isCircleCollision(const Circle& circle) const {
    float circleDistanceX = abs(circle.x - (x + width / 2));
    float circleDistanceY = abs(circle.y - (y + height / 2));

    if (circleDistanceX > (width / 2 + circle.radius)) {
        return false;
    }
    if (circleDistanceY > (height / 2 + circle.radius)) {
        return false;
    }

    return true;
}

void Platform::resolveCircleCollision(Circle& circle) {
    float closestX = std::max(x, std::min(circle.x, x + width));
    float closestY = std::max(y, std::min(circle.y, y + height));

    float distanceX = circle.x - closestX;
    float distanceY = circle.y - closestY;

    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    if (distanceSquared < circle.radius * circle.radius) {
        // Collision detected, resolve it

        float distance = std::sqrt(distanceSquared);
        float overlap = circle.radius - distance;

        float normalX = distanceX / distance;
        float normalY = distanceY / distance;

        // Update the circle's position to separate it from the platform
        circle.x += overlap * normalX;
        circle.y += overlap * normalY;

        // Reflect the circle's velocity based on the platform's orientation
        float dotProduct = circle.vx * normalX + circle.vy * normalY;

        if (dotProduct < 0) {
            
            circle.vx -= 1.8f * dotProduct * normalX;
            circle.vy -= 1.8f * dotProduct * normalY;
        }
    }
}

bool Platform::isCustomShapeCollision(const CustomShape& customShape) const {
    // Implement your collision detection logic with the custom shape here
    // Replace the following line with your custom logic
    return (x < customShape.x + customShape.width &&
        x + width > customShape.x &&
        y < customShape.y + customShape.height &&
        y + height > customShape.y);
}

void Platform::resolveCustomShapeCollision(CustomShape& customShape) {
    // Calculate overlap in each dimension
    float overlapX = std::min(x + width, customShape.x + customShape.width) - std::max(x, customShape.x);
    float overlapY = std::min(y + height, customShape.y + customShape.height) - std::max(y, customShape.y);

    // Resolve collision based on the smaller overlap
    if (overlapX < overlapY) {
        // Resolve collision along the X-axis
        if (x + width / 2 < customShape.x + customShape.width / 2) {
            // Platform is to the left of the custom shape
            customShape.x = x + width;
        }
        else {
            // Platform is to the right of the custom shape
            customShape.x = x ;
        }

        // Reverse the custom shape's velocity and adjust to avoid overlap
        customShape.vx = -customShape.vx * 0.6; // Tweak the factor as needed
    }
    else {
        // Resolve collision along the Y-axis
        if (y + height / 2 < customShape.y + customShape.height / 2) {
            // Platform is below the custom shape
            customShape.y = y + customShape.height;
        }
        else {
            // Platform is above the custom shape
            customShape.y = y - customShape.height;
        }

        // Reverse the custom shape's velocity and adjust to avoid overlap
        customShape.vy = -customShape.vy * 0.5; // Tweak the factor as needed

        

    }
}

void Platform::Movement(int key, int action, int maxX, int maxY) {
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (x > 0 && x < maxX - 100 && y>10 && y < maxY - 10)) {
        //Move the platform based on the key pressed
        switch (key) {
        case GLFW_KEY_LEFT:
            x -= 20;
            break;
        case GLFW_KEY_RIGHT:
            x += 20;
            break;
        case GLFW_KEY_UP:
            y += 20;
            break;
        case GLFW_KEY_DOWN:
            y -= 20;
            break;
        }
    }
    else if (action == GLFW_PRESS || action == GLFW_REPEAT) {//keeping the platform in bounds
            if (x <= 0) {
                x += 50;
            }
            if (x >= maxX - 100) {
                x -= 50;
            }
            if (y <= 20) {
                y += 10;
            }
            if (y >= maxY - 40) {
                y -= 20;
            }
    }
}