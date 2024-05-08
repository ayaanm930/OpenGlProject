#include "Circle.h"
#include <cmath>
#include <GLFW/glfw3.h>
#include <algorithm>
const int windowWidth = 800;
const int windowHeight = 600;
Circle::Circle(float x, float y, float radius, float vx, float vy, float colorR, float colorG, float colorB, float mass)
    : x(x), y(y), radius(radius), vx(vx), vy(vy), colorR(colorR), colorG(colorG), colorB(colorB), mass(mass), ax(0.0f), ay(0.0f) {}

void Circle::update(float dt) {
    x += vx * dt;
    y += vy * dt;

    // Check window boundaries and reverse velocity if necessary
    if (x - radius < 0 || x + radius > windowWidth) {
        vx = -vx;
        // Correct position to stay inside the boundary
        x = std::max(radius, std::min(x, windowWidth - radius));
    }
    if (y - radius < 0 || y + radius > windowHeight) {
        vy = -vy;
        // Correct position to stay inside the boundary
        y = std::max(radius, std::min(y, windowHeight - radius));
    }
    updateAcceleration();
}

void Circle::draw() const {
    glColor3f(colorR, colorG, colorB);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159265 / 180.0;
        float x = this->x + this->radius * cos(angle);
        float y = this->y + this->radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

bool Circle::isCircleCollision(const Circle& other) const {
    float distance = sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    return distance < (radius + other.radius);
}

void Circle::resolveCircleCollision(Circle& other) {
    float dx = other.x - x;
    float dy = other.y - y;
    float distance = sqrt(dx * dx + dy * dy);
    float overlap = (radius + other.radius) - distance;
    if (overlap>0) {
        // Calculate the displacement needed for separation
        float displacementX = (overlap / distance) * dx;
        float displacementY = (overlap / distance) * dy;
        // Update positions to separate circles
        x -= displacementX / 2;
        y -= displacementY / 2;
        other.x += displacementX / 2;
        other.y += displacementY / 2;

        //Calculate collision normal
        float normalX = dx / distance;
        float normalY = dy / distance;

        //Relative Velocity
        float rvx = other.vx - vx;
        float rvy = other.vy - vy;
        float rSpeed = (rvx * normalX) + (rvy * normalY);

        //Impulse
        float res = 2; //illasticity
        float imp = (2.0f * rSpeed) / ((1 / mass) + (1 / other.mass));
        vx += (imp / mass) * normalX;
        vy += (imp / mass) * normalY;
        other.vx -= (imp / other.mass) * normalX;
        other.vy -= (imp / other.mass) * normalY;

        ax += 0.1f;
        ay += 0.1f;
        other.ax += 0.1f;
        other.ay += 0.1f;


        /*
        // Reflect velocities for a simple collision response
        float dotProduct = (vx * dx + vy * dy) / (distance * distance);
        vx = 2 * dotProduct * dx - vx;
        vy = 2 * dotProduct * dy - vy;

        dotProduct = (other.vx * dx + other.vy * dy) / (distance * distance);
        other.vx = 2 * dotProduct * dx - other.vx;
        other.vy = 2 * dotProduct * dy - other.vy;
        ax += 0.1f;
        ay += 0.1f;
        */
    }
}

float Circle::calculateMomentum() const {
    return mass * sqrt(vx * vx + vy * vy);
}

void Circle::updateAcceleration() {
    // Example: Gravity force
    const float gravityForce = 9.8f;  // Adjust as needed

    // Update acceleration based on external forces
    ay -= gravityForce / mass;
}


void Circle::collisionColor(Circle& other) {
    colorR = static_cast<float>(rand()) / RAND_MAX;
    colorG = static_cast<float>(rand()) / RAND_MAX;
    colorB = static_cast<float>(rand()) / RAND_MAX;

    glColor3f(colorR, colorG, colorB);


}
