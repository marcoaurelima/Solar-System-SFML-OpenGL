#ifndef SPACESHIP_H
#define SPACESHIP_H

#pragma once

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <climits>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SOIL/SOIL.h>

#include <SFML/Window.hpp>

#define QTD_FACES 200

struct Size
{
    Size(GLfloat w, GLfloat h)
    : w(w), h(h){}

    GLfloat w, h;
};

class SpaceShip
{
public:
    SpaceShip(glm::vec3 initialPosition, Size windowSize);
    ~SpaceShip();   

    void show(sf::Window& window);
    void moveCameraView(sf::Vector2i mousePos);
    void moveCameraPosition();
    void handleKeyboardInput();
    void handleJoystickInput();
    glm::vec3 getCamPosition();
private:
    glm::vec3 camPosition;
    glm::vec3 camAt;
    glm::vec3 camUp = glm::vec3(0, 1, 0);
    Size windowSize;
    float velocity = 25;
    GLuint texture {};

    float sensibility = 0.1f;
    bool firstMouse = true;
    float angleX   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float angleY =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
};

#endif