/*M. Ayaan Mughal
22i-0861
OOP_LAB
OpenGL Project*/


#include "Circle.h"
#include "CustomShape.h"
#include "Boundary.h"
#include "Platform.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <vector>
#include <random>


const int windowWidth = 900;
const int windowHeight = 650;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Platform* platform = static_cast<Platform*>(glfwGetWindowUserPointer(window));

    if (platform) {
        platform->Movement(key, action,900,650);
    }
}

int main() {

    srand(time(0));

    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Collision Detection", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    float x1;
    float y1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(100.0f, 900.0f);

    float randomFloat = dis(gen);
       y1 = dis(gen);
   
   
    // Create a single instance of CustomShape
    CustomShape customShape(randomFloat, y1, 30, 30, 4.0f, 4.0f, 0.0f, 0.0f, 1.0f);
  

    // Ask the user how many circles they want to draw
    int numCircles;
    std::cout << "Enter the number of circles: ";
    std::cin >> numCircles;
   
    std::vector<Circle> circles;

    for (int i = 0; i < numCircles; ++i) {
        float xPos = rand() % windowWidth;
        float yPos = rand() % windowHeight;
        float radius = 20.0f;  // Fixed radius for all circles
        float vx = (rand() % 200 - 100) * 0.2;  // Slower random velocity between -20 and 20
        float vy = (rand() % 200 - 100) * 0.2;  // Slower random velocity between -20 and 20
        float colorR = static_cast<float>(rand()) / RAND_MAX;  // Random color component
        float colorG = static_cast<float>(rand()) / RAND_MAX;  // Random color component
        float colorB = static_cast<float>(rand()) / RAND_MAX;  // Random color component

        // Modified constructor call with mass
        float mass = 1.0f;  // Adjust the mass value as needed
        circles.emplace_back(xPos, yPos, radius, vx, vy, colorR, colorG, colorB, mass);
    }
   
   

    Platform platform(300, 400, 100, 20, 50, 0);
    //set user pointer to platform and set callback function
    glfwSetWindowUserPointer(window, &platform);
    glfwSetKeyCallback(window, keyCallback);

    Boundary boundary;

    int printCounter = 0;
    const int printFrequency = 100;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the boundaries
        boundary.draw();


        // Update and draw circles
        for (auto& circle : circles) {
            circle.updateAcceleration();
            circle.update(0.01);
            circle.draw();

            // Check for collisions with the boundary
            boundary.resolveCircleCollision(circle);
            
            if (customShape.isCircleCollision(circle)) {
                customShape.resolveCircleCollision(circle);
            }
            // Check for collisions between circles
            for (auto& otherCircle : circles) {
                if (&circle != &otherCircle && circle.isCircleCollision(otherCircle)) {
                    circle.resolveCircleCollision(otherCircle);
                    circle.collisionColor(otherCircle);
                }
            }

            // Check for collisions with the platform
            if (platform.isCircleCollision(circle)) {
                platform.resolveCircleCollision(circle);
            }
            // Print velocity, acceleration, and momentum with a frequency
            //printCounter++;
            //if (printCounter == printFrequency) {
            //    std::cout << "Circle Velocity: (" << circle.vx << ", " << circle.vy << ") ";
            //    std::cout << "Acceleration: (" << circle.ax << ", " << circle.ay << ") ";
            //    std::cout << "Momentum: " << circle.calculateMomentum() << std::endl;

            //    printCounter = 0;  // Reset the counter
            //}
             // Display velocity, acceleration, and momentum
            printCounter++;
            if (printCounter == printFrequency) {
                std::cout << "Circle Velocity: (" << circle.vx << ", " << circle.vy << ")" << std::endl;
                std::cout << "Circle Acceleration: (" << circle.ax << ", " << circle.ay << ")" << std::endl;
                std::cout << "Circle Momentum: (" << circle.vx * circle.mass << ", " << circle.vy * circle.mass << ")" << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                printCounter = 0;
            }
            
        }
        // Update and draw the single custom shape
        customShape.update(0.1);
        customShape.draw();

        // Check for collisions with the boundary
        boundary.resolveCustomShapeCollision(customShape);

        // Check for collisions with the platform
        if (platform.isCustomShapeCollision(customShape)) {
            platform.resolveCustomShapeCollision(customShape);
        }

        // Update and draw platform
        platform.update(0.01);
        platform.draw();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
