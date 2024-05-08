#include "Boundary.h"
#include <GLFW/glfw3.h>
#include <algorithm>

const int windowWidth = 900;
const int windowHeight = 650;

void Boundary::draw() const {
    glLineWidth(10.0f);
    glColor3f(2.0f, 0.5f, 1.0f);  // White color for the boundary

    // Draw top boundary
    glBegin(GL_LINES);
    glVertex2f(0, windowHeight);
    glVertex2f(windowWidth, windowHeight);
    glEnd();

    // Draw bottom boundary
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glEnd();

    // Draw left boundary
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw right boundary
    glBegin(GL_LINES);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glEnd();

    // Draw center plus sign boundary
    float boundaryThickness = 4;  // Adjust as needed
    glBegin(GL_LINES);
    // Horizontal lines
    glVertex2f(0, windowHeight / 2 - boundaryThickness);
    glVertex2f(windowWidth, windowHeight / 2 - boundaryThickness);
    glVertex2f(0, windowHeight / 2 + boundaryThickness);
    glVertex2f(windowWidth, windowHeight / 2 + boundaryThickness);
    // Vertical lines
    glVertex2f(windowWidth / 2 - boundaryThickness, 0);
    glVertex2f(windowWidth / 2 - boundaryThickness, windowHeight);
    glVertex2f(windowWidth / 2 + boundaryThickness, 0);
    glVertex2f(windowWidth / 2 + boundaryThickness, windowHeight);
    glEnd();
}

bool Boundary::isCircleInside(const Circle& circle) const {
    return circle.x - circle.radius > 0 &&
        circle.x + circle.radius < windowWidth &&
        circle.y - circle.radius > 0 &&
        circle.y + circle.radius < windowHeight;
}

void Boundary::resolveCircleCollision(Circle& circle) {
    // Resolve collision with the boundaries

    // Check left and right boundaries
    if (circle.x - circle.radius < 0 || circle.x + circle.radius > windowWidth) {
        circle.vx = -circle.vx;
        // Correct position to stay inside the boundary
        circle.x = std::max(circle.radius, std::min(circle.x, windowWidth - circle.radius));
    }

    // Check top and bottom boundaries
    if (circle.y - circle.radius < 0 || circle.y + circle.radius > windowHeight) {
        circle.vy = -circle.vy;
        // Correct position to stay inside the boundary
        circle.y = std::max(circle.radius, std::min(circle.y, windowHeight - circle.radius));
    }

    // Check center plus sign boundary
    float boundaryThickness = 2.0f;  // Adjust as needed
    if (circle.x + circle.radius >= windowWidth / 2 - boundaryThickness &&
        circle.x - circle.radius <= windowWidth / 2 + boundaryThickness) {
        circle.vx = -circle.vx;
        // Correct position to stay inside the boundary
        if (circle.x < windowWidth / 2) {
            circle.x = windowWidth / 2 - boundaryThickness - circle.radius;
        }
        else {
            circle.x = windowWidth / 2 + boundaryThickness + circle.radius;
        }
    }

    if (circle.y + circle.radius >= windowHeight / 2 - boundaryThickness &&
        circle.y - circle.radius <= windowHeight / 2 + boundaryThickness) {
        circle.vy = -circle.vy;
        // Correct position to stay inside the boundary
        if (circle.y < windowHeight / 2) {
            circle.y = windowHeight / 2 - boundaryThickness - circle.radius;
        }
        else {
            circle.y = windowHeight / 2 + boundaryThickness + circle.radius;
        }
    }
}

void Boundary::resolveCustomShapeCollision(CustomShape& customShape) {
    // Resolve collision with the boundaries

    // Check left and right boundaries
    if (customShape.x - customShape.width / 2 < 0 || customShape.x + customShape.width / 2 > windowWidth) {
        customShape.vx = -customShape.vx;
        // Correct position to stay inside the boundary
        customShape.x = std::max(customShape.width / 2, std::min(customShape.x, windowWidth - customShape.width / 2));
    }

    // Check top and bottom boundaries
    if (customShape.y - customShape.height / 2 < 0 || customShape.y + customShape.height / 2 > windowHeight) {
        customShape.vy = -customShape.vy;
        // Correct position to stay inside the boundary
        customShape.y = std::max(customShape.height / 2, std::min(customShape.y, windowHeight - customShape.height / 2));
    }
}
