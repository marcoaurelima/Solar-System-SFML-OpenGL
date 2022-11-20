#ifndef SPACESHIP_H
#define SPACESHIP_H

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <climits>
#include <glm/glm.hpp>
#include <glm/ext.hpp>



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

    void show();
private:
    glm::vec3 position;
    Size windowSize;
};

#endif