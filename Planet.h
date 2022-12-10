#ifndef PLANET_H
#define PLANET_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>

#define QTD_FACES 200

#include "Object.h"

class Planet
{
public:
    Planet(GLfloat rotationVelocity, GLfloat translationVelocity, GLfloat orbitRadius, GLdouble size, std::string texturePath);
    ~Planet();
    
    GLdouble getOrbitValue();
    void show();

private:
    GLfloat translation {};
    GLfloat translationVelocity {};
	GLfloat rotation {};
	GLfloat rotationVelocity {};
	GLfloat orbitRadius {};
    GLdouble size {};
	GLuint texture {};

    void createSphere(GLdouble radius);
    Object obj;
};

#endif