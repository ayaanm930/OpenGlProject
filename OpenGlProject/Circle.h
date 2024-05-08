#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
public:
    float x, y;  // Position
    float radius;
    float ax, ay;  // Acceleration
    float vx, vy;  // Velocity
    float colorR, colorG, colorB;  // Color components
    float mass;  // Mass of the circle

    Circle(float x, float y, float radius, float vx, float vy, float colorR, float colorG, float colorB, float mass);

    void update(float dt);
    void printInfo() const;
    void draw() const;

    bool isCircleCollision(const Circle& other) const;
    void resolveCircleCollision(Circle& other);
    
    float calculateMomentum() const;
    void updateAcceleration();
    void collisionColor(Circle& other);
};

#endif // CIRCLE_H
