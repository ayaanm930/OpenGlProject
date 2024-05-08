#include "CustomShape.h"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

CustomShape::CustomShape(float x, float y, float width, float height, float vx, float vy, float ax, float ay, float mass)
    : x(x), y(y), width(width), height(height), vx(vx), vy(vy), ax(ax), ay(ay), mass(mass) {}

void CustomShape::update(float dt) {
    // Update acceleration based on external forces (e.g., gravity)
    // Add your external forces or behaviors here
    float externalForceY = -0.00000001;
    // ax += externalForceX / mass;
     ay += externalForceY / mass;

    // Update velocity based on acceleration
    vx += ax * dt;
    vy += ay * dt;

    // Update position based on velocity
    x += vx * dt;
    y += vy * dt;
}

void CustomShape::draw() const {
    // Add code to draw your custom shape (e.g., using OpenGL functions)
    // 
    // Replace this with your custom drawing code
    glColor3f(1.0f, 0.0f, 1.0f);  // Purple color for the custom shape
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + width / 2, y + height / 2); //center of hexagon
    float radius = std::min(width, height) / 2.0f;

    for (int i = 0; i <=6; i++) { //6 points of hexagon
        float angle = i * (2 * 3.14 / 6);
        float outX = x + width / 2 + radius * cos(angle);
        float outY = y + height / 2 + radius * sin(angle);
        glVertex2f(outX, outY);

        float inX = x + width / 2 + radius / 2 * cos(angle + 3.14 / 6);
        float inY = y + height / 2 + radius / 2 * sin(angle + 3.14 / 6);
        glVertex2f(inX, inY);

    }

   /* glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);*/
    glEnd();
}

bool CustomShape::isCircleCollision(const Circle& circle) const {
    // Calculate the distance between the center of the circle and the closest point on the rectangle
    float closestX = std::max(x, std::min(circle.x, x + width));
    float closestY = std::max(y, std::min(circle.y, y + height));

    // Calculate the distance between the circle's center and the closest point on the rectangle
    float distanceX = circle.x - closestX;
    float distanceY = circle.y - closestY;

    // Check if the distance is less than the circle's radius, indicating a collision
    return (distanceX * distanceX + distanceY * distanceY) < (circle.radius * circle.radius);
}

void CustomShape::resolveCircleCollision(Circle& circle) {
    // Calculate the distance between the center of the circle and the closest point on the rectangle
    float closestX = std::max(x, std::min(circle.x, x + width));
    float closestY = std::max(y, std::min(circle.y, y + height));

    // Calculate the distance between the circle's center and the closest point on the rectangle
    float distanceX = circle.x - closestX;
    float distanceY = circle.y - closestY;

    // Calculate the overlap between the circle and the rectangle
    float overlap = circle.radius - std::sqrt(distanceX * distanceX + distanceY * distanceY);

    // Calculate the normalized direction from the circle to the rectangle
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);
    float directionX = distanceX / std::sqrt(distanceX * distanceX + distanceY * distanceY);
    float directionY = distanceY / std::sqrt(distanceX * distanceX + distanceY * distanceY);

    float dotProduct = circle.vx * directionX + circle.vy * directionY;
    if (dotProduct < 0) {

        circle.vx -= 2.0f * dotProduct * directionX;
        circle.vy -= 2.0f * dotProduct * directionY;
    }
    else {
        circle.vx += 2.0f * dotProduct * directionX;
        circle.vy += 2.0f * dotProduct * directionY;
    }
    // Update the position of the circle to move it outside the rectangle
    circle.x += overlap * directionX;
    circle.y += overlap * directionY;

    circle.ax += 0.2f;
    circle.ay += 0.2f;
}
