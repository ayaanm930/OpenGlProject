#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "Circle.h"
#include "CustomShape.h"  // Include the CustomShape class header

class Boundary {
public:
    void draw() const;

    bool isCircleInside(const Circle& circle) const;

    void resolveCircleCollision(Circle& circle);

    void resolveCustomShapeCollision(CustomShape& customShape);
};

#endif // BOUNDARY_H
