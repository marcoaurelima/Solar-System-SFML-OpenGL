#ifndef SUN_H
#define SUN_H

#pragma once

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL/SOIL.h>

#define QTD_FACES 200

/*const float DIFUSE = 1;
const float SPECULAR = 0;
const float POSITIONAL = 1;
const float GLOBAL = 0.2;
*/
struct LightParameters
{
    LightParameters(){}
    LightParameters(GLfloat diffuse, GLfloat specular, GLfloat positional,  GLfloat global)
    : diffuse(diffuse), specular(specular), positional(positional), global(global){}

    GLfloat diffuse;
    GLfloat specular;
    GLfloat positional;
    GLfloat global;
};

class Sun
{
public:
    Sun(GLdouble size, std::string texturePath, LightParameters lp);
    ~Sun();

    void illuminate();

private:
    GLdouble size{};
    GLuint texture{};
    void createSphere(GLdouble radius);

    LightParameters lp;
    
    GLfloat* ambientLight;
    GLfloat* diffuseLight;
    GLfloat* specularlight;
    GLfloat* positionalLight;
    GLfloat* globalLight;
};

#endif