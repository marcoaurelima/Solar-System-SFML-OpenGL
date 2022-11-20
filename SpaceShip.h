#ifndef SPACESHIP_H
#define SPACESHIP_H

#pragma once

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <climits>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <SFML/Window.hpp>

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
private:
    glm::vec3 position;
    glm::vec3 at;
    Size windowSize;
};

#endif