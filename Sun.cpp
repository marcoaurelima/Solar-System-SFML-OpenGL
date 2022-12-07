#include "Sun.h"

Sun::Sun(GLdouble size, LightParameters lp, std::string texturePath)
{
    ambientLight =    new GLfloat[4]{0.0, 0.0, 0.0, 1.0};
    diffuseLight =    new GLfloat[4]{lp.diffuse, lp.diffuse, lp.diffuse, 1.0};
    specularlight =   new GLfloat[4]{lp.specular, lp.specular, lp.specular, 1.0};
    positionalLight = new GLfloat[4]{0.0, 0.0, 3.0, lp.positional};
    globalLight =     new GLfloat[4]{lp.global, lp.global, lp.global, 1.0};

    this->lp = lp;
    this->size = size;

    sphere.loadFromFile("models/esfera.obj");
    sphere.loadTextureFile("textures/sun.jpg");
}

Sun::~Sun()
{
}


void Sun::illuminate()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularlight);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLight);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, positionalLight);
    glTranslatef(positionalLight[0], positionalLight[1], positionalLight[2]);
    glColor3f(lp.diffuse, lp.diffuse, lp.diffuse);

    // Renderizar o sol
    glScalef(size,size,size);
    sphere.show();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}